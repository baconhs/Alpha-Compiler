#include "vm.h"
#include <assert.h>

double *numConsts = NULL;
unsigned totalNumConsts = 0;
char **stringConsts = NULL;
unsigned totalStringConsts = 0;
char **namedLibfuncs = NULL;
unsigned totalNamedLibfuncs = 0;
struct userfunc **userFuncs = NULL;
unsigned int totalUserFuncs = 0;
unsigned totGlobals = 0;

avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx, retval;
instruction *code = NULL;
unsigned char executionFinished = 0;
unsigned pc = 1, currLine = 0, codeSize = 0, top = AVM_STACKSIZE - 1, topsp = AVM_STACKSIZE - 1, totalActuals = 0;

char *typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};

void avm_error(char *format)
{
    printf("\x1b[31mError:\x1b[0m %s line %d\n", format, currLine);
    executionFinished = 1;
}

void avm_warning(char *format)
{
    printf("%d: warning: %s\n", currLine, format);
}

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{

    switch (arg->type)
    {

    case global_a:
        return &stack[AVM_STACKSIZE - 1 - arg->val];

    case local_a:
    {

        return &stack[topsp - arg->val];
    }
    case formal_a:
    {
        return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
    }
    case retval_a:
        return &retval;

    case number_a:
    {
        reg->type = number_m;
        reg->data.numVal = consts_getnumber(arg->val);
        return reg;
    }

    case string_a:
    {
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstring(arg->val));
        return reg;
    }

    case bool_a:
    {
        reg->type = bool_m;
        reg->data.boolVal = (arg->val);
        return reg;
    }

    case nil_a:
    {
        reg->type = nil_m;
        return reg;
    }

    case userfunc_a:
    {
        reg->type = userfunc_m;
        reg->data.funcVal = funcs_get_address(arg->val);
        return reg;
    }

    case libfunc_a:
    {
        reg->type = libfunc_m;
        reg->data.libfuncVal = libfuncs_getused(arg->val);
        return reg;
    }

    default:
        assert(0);
    }
}

typedef unsigned char (*tobool_func_t)(avm_memcell *);

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool};

typedef void (*execute_func_t)(instruction *);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_jump,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    // execute_newtable,
    // execute_tablegetelem,
    // execute_tablesetelem
};

typedef char *(*tostring_func_t)(avm_memcell *);

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring};

typedef double (*arithmetic_func_t)(double x, double y);

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

typedef unsigned (*compare_func_t)(double x, double y);

compare_func_t compareFuncs[] = {
    le,
    ge,
    lt,
    gt,
};

typedef void (*library_func_t)(void);

library_func_t library_funcs[] = {
    libfunc_print,
    libfunc_typeof,
    libfunc_totalarguments,
    libfunc_argument,
};

typedef void (*memclear_func_t)(avm_memcell *);

memclear_func_t memclearFuncs[] = {0, memclear_string, 0, memclear_table, 0, 0, 0, 0};

void avm_memcell_clear(avm_memcell *m)
{
    if (m->type == undef_m)
        return;
    memclear_func_t f = memclearFuncs[m->type];
    if (f)
    {
        (*f)(m);
    }
    m->type = undef_m;
}

void execute_arithmetic(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)+0);
    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_error("not a number in arithmetic!");
    }
    else
    {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

void execute_compare(instruction *instr)
{

    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);
    int res = 0;
    assert(rv1 && rv2 && instr->result->type == label_a);

    if (rv1->type != number_m || rv2->type != number_m)
    {
        avm_error("not num_type in comparison!");
    }
    else
    {
        compare_func_t op = compareFuncs[instr->opcode - jle_v];
        res = (*op)(rv1->data.numVal, rv2->data.numVal);
    }

    if (res)
    {
        pc = instr->result->val;
    }
}

unsigned char number_tobool(avm_memcell *m)
{
    return m->data.numVal != 0;
}
unsigned char string_tobool(avm_memcell *m)
{
    return m->data.strVal[0] != 0;
}
unsigned char bool_tobool(avm_memcell *m)
{
    return m->data.boolVal;
}

unsigned char table_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char userfunc_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char libfunc_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char nil_tobool(avm_memcell *m)
{
    return 0;
}

unsigned char undef_tobool(avm_memcell *m)
{
    assert(0);
    return 0;
}

unsigned char avm_tobool(avm_memcell *m)
{
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

void execute_cycle(void)
{
    if (executionFinished)
        return;
    else if (pc == AVM_ENDING_PC)
    {
        executionFinished = 1;
        return;
    }
    else
    {
        assert(pc < AVM_ENDING_PC);
        instruction *instr = code + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if (instr->srcLine)
            currLine = instr->srcLine;
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC)
            ++pc;
    }
}

void execute_assign(instruction *instr)
{

    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(instr->arg1, &ax);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);
    avm_assign(lv, rv);
}

void execute_uminus(instruction *instr) {}

void execute_and(instruction *instr) {}

void execute_or(instruction *instr) {}

void execute_not(instruction *instr) {}

void execute_jeq(instruction *instr)
{
    assert(instr->result->type == label_a);

    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("There is an'Undef' involved in equality!\n");
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if (rv1->type == bool_m || rv2->type == bool_m)
    {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type)
        avm_error(" == is illegal! due to type mismatch\n");
    else
    {
        if (rv1->type == string_m)
        {
            if (!strcmp(rv1->data.strVal, rv2->data.strVal))
                result = 1;
            else
                result = 0;
        }
        else if (rv1->type == number_m)
        {
            if (rv1->data.numVal == rv2->data.numVal)
                result = 1;
            else
                result = 0;
        }
        else
        {
            if ((toboolFuncs[rv1->type])(rv1) == (toboolFuncs[rv1->type])(rv2))
                result = 1;
            else
                result = 0;
        }
    }

    if (!executionFinished && result)
        pc = instr->result->val;
}

void execute_jne(instruction *instr)
{
    assert(instr->result->type == label_a);

    avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("There is an'Undef' involved in equality!\n");
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type != rv2->type)
        avm_error(" == is illegal! due to type mismatch\n");
    else
    {
        if (rv1->type == string_m)
        {
            if (strcmp(rv1->data.strVal, rv2->data.strVal))
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
        }
        else if (rv1->type == number_m)
        {
            if (rv1->data.numVal != rv2->data.numVal)
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
        }
        else
        {
            if ((*toboolFuncs[rv1->type])(rv1) != (*toboolFuncs[rv1->type])(rv2))
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
        }
    }

    if (!executionFinished && result)
        pc = instr->result->val;
}

void execute_jump(instruction *instr)
{
    assert(instr->result->type == label_a);
    pc = instr->result->val;
}

void execute_call(instruction *instr)
{

    avm_memcell *func = avm_translate_operand(instr->result, &ax);

    assert(func);
    avm_callsaveenviroment();
    switch (func->type)
    {
    case userfunc_m:
    {

        pc = func->data.funcVal;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
        break;
    }
    case string_m:
    {
        avm_calllibfunc(func->data.strVal);
        break;
    }
    case libfunc_m:
    {

        avm_calllibfunc(func->data.libfuncVal);
        break;
    }
    default:
        avm_error("call: cannot bind this to function!\n");
    }
}

void execute_pusharg(instruction *instr)
{

    avm_memcell *arg = avm_translate_operand(instr->result, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(instruction *instr)
{

    avm_memcell *func = avm_translate_operand(instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);

    totalActuals = 0;
    userfunc *f = avm_getfuncinfo(pc);
    topsp = top;
    top = top - f->localSize;
}

void execute_funcexit(instruction *unused)
{

    unsigned oldTop = top;
    top = avm_get_envvalue(topsp AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);

    while (++oldTop <= top)
    {
        avm_memcellclear(&stack[oldTop]);
    }
}

void execute_newtable(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
    assert(lv && ((&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top]) || lv == &retval));

    avm_memcell_clear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

char *number_tostring(avm_memcell *m)
{
    char number[100];
    sprintf(number, "%g", m->data.numVal);
    return strdup(number);
}

char *string_tostring(avm_memcell *m)
{
    return strdup(m->data.strVal);
}

char *bool_tostring(avm_memcell *m)
{

    if (m->data.boolVal == 1)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

char *table_tostring(avm_memcell *m)
{
    return "Table den exei. Telos. Den me noiazei re file.";
}

char *userfunc_tostring(avm_memcell *m)
{

    char *result = malloc(11 + m->data.funcVal);
    strcpy(result, "user func ");
    strcat(result, m->data.funcVal);
    return result;
}

char *libfunc_tostring(avm_memcell *m)
{
    char *result = malloc(14 + strlen(m->data.libfuncVal));
    strcpy(result, "library func ");
    strcat(result, m->data.libfuncVal);
    return result;
}

char *nil_tostring(avm_memcell *m)
{
    return "nil";
}

char *undef_tostring(avm_memcell *m)
{
    return "undef";
}

double add_impl(double x, double y)
{
    return x + y;
}

double sub_impl(double x, double y)
{
    return x - y;
}

double mul_impl(double x, double y)
{
    return x * y;
}

double div_impl(double x, double y)
{
    if (y != 0)
        return x / y;
    avm_error("Divisor can't be 0");
    return -1;
}

double mod_impl(double x, double y)
{
    if (y != 0)
        return ((unsigned)x) % ((unsigned)y);
    avm_error("Divisor can't be 0");
    return -1;
}

unsigned le(double x, double y)
{
    return x <= y;
}

unsigned ge(double x, double y)
{
    return x >= y;
}

unsigned lt(double x, double y)
{
    return x < y;
}

unsigned gt(double x, double y)
{
    return x > y;
}

void libfunc_print(void)
{
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i)
    {
        char *s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

void libfunc_typeof(void)
{
    unsigned n = avm_totalactuals();

    if (n != 1)
    {
        avm_error("one argument not expected in typeof!");
        printf("the argument not found is %d\n", n);
    }
    else
    {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments(void)
{
    unsigned p_topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if (!p_topsp)
    {
        avm_error("/'totalarguments'/ called outside a function!");
        retval.type = nil_m;
    }
    else
    {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument()
{
    unsigned p_topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);

    unsigned n = avm_get_envvalue(topsp AVM_NUMACTUALS_OFFSET);
    unsigned arg = avm_getactual(0)->data.numVal;
    unsigned num_actuals = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);

    if (!p_topsp)
    {
        avm_error("\'argument\' called outside a function!");
        retval.type = nil_m;
    }
    else if (n != 1)
    {
        avm_error("Expected ONE argument in \'argument\'!");
        retval.type = nil_m;
    }
    else if (arg < 0)
    {
        avm_error("Index cannot be negative in \'argument\'!");
        retval.type = nil_m;
    }
    else if (arg > num_actuals)
    {
        avm_error("Index bigger than total arguments in \'argument\'!");
        retval.type = nil_m;
    }
    else
    {
        avm_memcell *actual = &stack[p_topsp AVM_NUMACTUALS_OFFSET + arg + 1];
        retval.type = actual->type;
        if (retval.type == string_m)
        {
            retval.data.strVal = strdup(actual->data.strVal);
        }
        else
        {
            retval.data = actual->data;
        }
    }
}

userfunc *avm_getfuncinfo(unsigned address)
{
    for (unsigned int i = 0; i < totalUserFuncs; i++)
    {
        if (address == userFuncs[i]->address)
        {
            return userFuncs[i];
        }
    }
    avm_error("User function not found");
    assert(0);
}

unsigned get_libfunc_id(char *name)
{

    if (strcmp(name, "print") == 0)
    {
        return 0;
    }
    else if (strcmp(name, "typeof") == 0)
    {
        return 1;
    }
    else if (strcmp(name, "totalarguments") == 0)
    {
        return 2;
    }
    else if (strcmp(name, "argument") == 0)
    {
        return 3;
    }
    else if (strcmp(name, "input") == 0)
    {
        return 4;
    }
    else if (strcmp(name, "strtonum") == 0)
    {
        return 5;
    }
    else if (strcmp(name, "sqrt") == 0)
    {
        return 6;
    }
    else if (strcmp(name, "cos") == 0)
    {
        return 7;
    }
    else if (strcmp(name, "sin") == 0)
    {
        return 8;
    }
    else if (strcmp(name, "objectmemberkeys") == 0)
    {
        return 9;
    }
    else if (strcmp(name, "objecttotalmembers") == 0)
    {
        return 10;
    }
    else if (strcmp(name, "objectcopy") == 0)
    {
        return 11;
    }
    else
    {
        return -1;
    }
}

library_func_t avm_getlibraryfunc(char *name)
{
    return (*library_funcs[get_libfunc_id(name)]);
}

void avm_tableincrefcounter(avm_table *t)
{
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter)
    {
        avm_tabledestroy(t);
    }
}

avm_table *avm_tablenew(void)
{
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
    for (unsigned int i = 0; i < AVM_TABLE_HASHSIZE; i++)
    {
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tablebucketdestroy(avm_memcell **p)
{
    for (unsigned int i = 0; i < AVM_TABLE_HASHSIZE; i++, p++)
    {
        for (avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tabledestroy(avm_table *t)
{
    avm_tablebucketdestroy(t->strIndexed);
    avm_tablebucketdestroy(t->numIndexed);
    free(t);
}

double consts_getnumber(unsigned index)
{
    return numConsts[index];
}

char *consts_getstring(unsigned index)
{
    return stringConsts[index];
}

char *libfuncs_getused(unsigned index)
{
    return namedLibfuncs[index];
}

unsigned funcs_get_address(unsigned index)
{
    return userFuncs[index]->address;
}

userfunc *funcs_get(unsigned index)
{
    return userFuncs[index];
}

void avm_memcellclear(avm_memcell *m)
{
    if (m->type != undef_m)
    {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
        {
            (*f)(m);
        }
        m->type = undef_m;
    }
}

void memclear_string(avm_memcell *m)
{
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell *m)
{
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{

    if (lv == rv)
    {
        return;
    }

    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    {
        return;
    }

    if (rv->type == undef_m)
    {
        avm_warning("assigning from 'undef' content!\n");
    }

    avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if (lv->type == string_m)
    {
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if (lv->type == table_m)
    {
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void avm_dec_top(void)
{
    if (!top)
    {
        avm_error("stack overflow\n");
    }
    else
    {
        --top;
    }
}

void avm_push_envvalue(unsigned val)
{
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenviroment(void)
{
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

unsigned avm_get_envvalue(unsigned i)
{

    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void avm_calllibfunc(char *id)
{
    library_func_t f = avm_getlibraryfunc(id);
    if (!f)
    {
        avm_error("unsupported lib func called ");
    }
    else
    {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if (!executionFinished)
        {
            execute_funcexit((instruction *)0);
        }
    }
}

unsigned avm_totalactuals(void)
{
    return avm_get_envvalue(topsp AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i)
{

    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

char *avm_tostring(avm_memcell *m)
{
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

void avm_initstack(void)
{
    for (unsigned i = 0; i < AVM_STACKSIZE; i++)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void add_vm_instr(instruction *instr, int i)
{
    if (!code)
        code = malloc(codeSize * sizeof(instruction));

    instruction *ins = code + i;
    ins->arg1 = malloc(sizeof(vmarg));
    ins->arg2 = malloc(sizeof(vmarg));
    ins->result = malloc(sizeof(vmarg));

    ins->opcode = instr->opcode;
    ins->arg1 = instr->arg1;
    ins->arg2 = instr->arg2;
    ins->result = instr->result;
    ins->srcLine = instr->srcLine;
}

void setGlobals(unsigned offset)
{
    if (offset > totGlobals)
        totGlobals = offset;
}

void read_bin_file()
{
    char *magicnumber[9];
    FILE *fp = fopen("alpha_bin.abc", "rb");
    if (!fp)
    {
        printf("bin file not found\n");
        exit(0);
    }
    fread(magicnumber, 9, 1, fp);

    fread(&totalStringConsts, sizeof(totalStringConsts), 1, fp);
    for (unsigned i = 0; i < totalStringConsts; i++)
    {
        int str_len = 0;
        fread(&str_len, sizeof(int), 1, fp);

        char *str_const = malloc(str_len);
        fread(str_const, str_len, 1, fp);

        if (!stringConsts)
        {
            stringConsts = malloc(totalStringConsts * sizeof(char *));
        }

        stringConsts[i] = str_const;
    }

    fread(&totalNumConsts, sizeof(totalNumConsts), 1, fp);
    for (unsigned i = 0; i < totalNumConsts; i++)
    {

        double num_const = 0;
        fread(&num_const, sizeof(double), 1, fp);

        if (!numConsts)
        {
            numConsts = malloc(totalNumConsts * sizeof(double));
        }

        numConsts[i] = num_const;
    }

    fread(&totalUserFuncs, sizeof(totalUserFuncs), 1, fp);
    for (unsigned i = 0; i < totalUserFuncs; i++)
    {
        userfunc *func = malloc(sizeof(userfunc));
        unsigned int func_name_length = 0;

        fread(&func_name_length, sizeof(unsigned int), 1, fp);
        func->id = malloc(func_name_length);

        fread(&func->address, sizeof(int), 1, fp);
        fread(&func->localSize, sizeof(int), 1, fp);
        fread(func->id, func_name_length, 1, fp);

        if (!userFuncs)
        {
            userFuncs = malloc(totalUserFuncs * sizeof(userfunc));
        }

        userFuncs[i] = func;
    }

    fread(&totalNamedLibfuncs, sizeof(totalNamedLibfuncs), 1, fp);
    for (unsigned i = 0; i < totalNamedLibfuncs; i++)
    {
        unsigned int str_len = 0;
        fread(&str_len, sizeof(int), 1, fp);

        char *lib_const = malloc(str_len);
        fread(lib_const, str_len, 1, fp);

        if (!namedLibfuncs)
        {
            namedLibfuncs = malloc(totalNamedLibfuncs * sizeof(char *));
        }

        namedLibfuncs[i] = lib_const;
    }

    fread(&codeSize, sizeof(codeSize), 1, fp);
    for (unsigned i = 1; i < codeSize; i++)
    {
        instruction *instr = malloc(sizeof(instruction));
        instr->result = malloc(sizeof(vmarg));
        instr->arg1 = malloc(sizeof(vmarg));
        instr->arg2 = malloc(sizeof(vmarg));

        fread(&instr->opcode, sizeof(vmarg_t), 1, fp);
        fread(&instr->result->type, sizeof(vmarg_t), 1, fp);
        fread(&instr->result->val, sizeof(int), 1, fp);
        fread(&instr->arg1->type, sizeof(vmarg_t), 1, fp);
        fread(&instr->arg1->val, sizeof(int), 1, fp);
        fread(&instr->arg2->type, sizeof(vmarg_t), 1, fp);
        fread(&instr->arg2->val, sizeof(int), 1, fp);
        if (instr->result->type == global_a)
            setGlobals(instr->result->val);
        if (instr->arg1->type == global_a)
            setGlobals(instr->arg1->val);
        if (instr->arg2->type == global_a)
            setGlobals(instr->arg2->val);
        fread(&instr->srcLine, sizeof(int), 1, fp);
        add_vm_instr(instr, i);
    }
}