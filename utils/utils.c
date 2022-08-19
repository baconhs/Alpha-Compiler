#include "utils.h"
#include "symtable.h"
#include <assert.h>

extern int yylineno;
extern SymTable_T hash_table;
extern char* yytext;
extern FILE* yyout;
extern unsigned int currQuad;
extern SymTable_T hash_table;
extern int curr_scope;
extern int temp_c;
extern int functionLocalOffset;
extern int anonymous;
extern int is_func;
extern int loop_c;
extern int stack_of_offsets;
quad* quads = NULL;
unsigned int total = 0;
unsigned int currQuad = 0;
int temp_c = 0;
funclist* function_list = NULL;
returnlist* return_list = NULL;

char* opcodes[] = {
    "ASSIGN", "ADD", "SUB", "MUL", "DIV", "MOD", "UMINUS", "AND", "OR", "NOT",
    "IF_EQ", "IF_NOTEQ", "IF_LESSEQ", "IF_GREATEREQ", "IF_LESS", "IF_GREATER",
    "JUMP", "CALL", "PARAM", "RETURN", "GETRETVAL", "FUNCSTART", "FUNCEND",
    "TABLECREATE", "TABLEGETELEM", "TABLESETELEM" };

int yyerror(const char* message) {
    fprintf(yyout, "\x1b[31mError:\x1b[0m %s line %d\n", message, yylineno);
    return 1;
}


void expand() {
    assert(total == currQuad);
    quad* p = malloc(NEW_SIZE);
    if (quads) {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned int label, unsigned int line) {

    if (currQuad == total)
        expand();
    quad* p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

void check_arith(expr* e, char* context) {
    if (e->type == constbool_e || e->type == conststring_e || e->type == nil_e || e->type == newtable_e || e->type == programfunc_e || e->type == libraryfunc_e || e->type == boolexpr_e) {
        yyerror(context);
    }
}

expr* emit_iftableitem(expr* e) {
    if (e && e->type != tableitem_e) {
        return e;
    }
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(tablegetelem, e, e->index, result, currQuad, yylineno);

    return result;
}

void push_funclist(int label) {
    funclist* new = malloc(sizeof(funclist));
    new->label = label;

    if (function_list) {
        new->prev = function_list;
        function_list = new;
    }
    else {
        function_list = new;
        function_list->prev = NULL;
    }
}

int pop_funclist() {
    funclist* temp = function_list;
    int label = temp->label;

    function_list = function_list->prev;
    free(temp);

    return label;
}

void push_returnlist(int label) {
    returnlist* new = malloc(sizeof(returnlist));
    new->label = label;

    if (return_list) {
        new->prev = return_list;
        return_list = new;
    }
    else {
        return_list = new;
        return_list->prev = NULL;
    }
}

int pop_returnlist() {
    returnlist* temp = return_list;
    int label = temp->label;
    return_list = return_list->prev;
    free(temp);
    return label;
}

char* newtempname() {
    char* tempname = malloc(100);
    sprintf(tempname, "_t%d", temp_c);
    return tempname;
}

SymbolTableEntry* newtemp() {
    char* name = newtempname();

    SymbolTableEntry* element = SymTable_get_element_from_scope(name, curr_scope);

    temp_c++;
    if (!element) {

        if (SymTable_insert(name, LOCAL) == 1) {

            return SymTable_get_element_from_type(name, LOCAL);

        }
        return NULL;
    }
    return element;
}

expr* newexpr(expr_t type) {
    expr* exp = calloc(1, sizeof(expr));
    exp->type = type;
    return exp;
}

expr* newexpr_constbool(unsigned int b) {
    expr* e = newexpr(constbool_e);
    if (b == 1) {
        e->boolConst = true;
    }
    else {
        e->boolConst = false;
    }
    return e;
}

expr* newexpr_constnum(double i) {
    expr* e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}

expr* newexpr_constint(int i) {
    expr* new = newexpr(constnum_e);
    new->numConst = i;
    return new;
}

expr* newexpr_conststring(char* str) {
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(str);
    return e;
}

expr* newexpr_constnil() {
    expr* new = newexpr(nil_e);
    return new;
}

unsigned int istempname(char* s) {
    return *s == '_';
}

unsigned int istempexpr(expr* e) {
    return e->sym && istempname(e->sym->name);
}


void patchlabel(unsigned quadNo, unsigned label) {
    assert(quadNo < currQuad && !quads[quadNo].label);
    quads[quadNo].label = label;
}

unsigned nextquad(void) { return currQuad; }

expr* lvalue_expr(SymbolTableEntry* sym) {
    assert(sym);
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->sym = sym;
    e->next = (expr*)0;

    switch (sym->type) {
    case FORMAL:
    case LOCAL:
    case GLOBAL:
    case NO_LOCAL:
        e->type = var_e;
        break;
    case USERFUNC:
        e->type = programfunc_e;
        break;
    case LIBFUNC:
        e->type = libraryfunc_e;
        break;
    default:
        assert(0);
    }
    return e;
}

void make_stmt(stmt_t* s) { s->breakList = s->contList = 0; }

int newlist(int i) {
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2) {
    if (!l1)
        return l2;
    else if (!l2)
        return l1;
    else {
        int i = l1;
        while (quads[i].label) { i = quads[i].label; }
        quads[i].label = l2;
        return l1;
    }
}

void patchlist(int list, int label) {
    while (list) {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

void reset_functionlocal_offset(int offset) {

    if (offset == -1) {
        functionLocalOffset = 0;
    }
    else {
        functionLocalOffset = offset;
    }
}


void reverse_list(expr* reversed_elist) {

    if (reversed_elist == NULL)
        return;

    reverse_list(reversed_elist->next);

    emit(param, reversed_elist, NULL, NULL, currQuad, yylineno);
}

expr* do_op(expr* exp1, expr* exp2, iopcode op) {
    check_arith(exp1, "can't do arithmetic operations on not arithmetic value");
    check_arith(exp2, "can't do arithmetic operations on not arithmetic value");
    expr* new = newexpr(arithexpr_e);
    if (istempexpr(exp1))
        new->sym = exp1->sym;
    else if (istempexpr(exp2))
        new->sym = exp2->sym;
    else
        new->sym = newtemp();
    emit(op, exp1, exp2, new, currQuad, yylineno);
    return new;
}

expr* do_uminus(expr* e) {
    check_arith(e, "can't do arithmetic operations on non arithmetic value");
    expr* term = newexpr(arithexpr_e);
    if (istempexpr(e))
        term->sym = e->sym;
    else
        term->sym = newtemp();
    emit(uminus, e, NULL, term, currQuad, yylineno);
    return term;
}

expr* do_post_dec_inc(expr* e, iopcode op) {
    check_arith(e, "can't do arithmetic operations on non arithmetic value");
    expr* term = newexpr(var_e);
    term->sym = newtemp();

    if (e->type == tableitem_e) {
        expr* val = emit_iftableitem(e);
        emit(assign, val, NULL, term, currQuad, yylineno);
        emit(op, val, newexpr_constint(1), val, currQuad, yylineno);
        emit(tablesetelem, e, e->index, val, currQuad, yylineno);
    }
    else {
        emit(assign, e, NULL, term, currQuad, yylineno);
        emit(op, e, newexpr_constint(1), e, currQuad, yylineno);
    }
    return term;
}

expr* do_pre_dec_inc(expr* e, iopcode op) {
    check_arith(e, "can't do arithmetic operations on non arithmetic value");
    if (e->type == tableitem_e) {
        expr* term = emit_iftableitem(e);
        emit(op, term, newexpr_constint(1), term, currQuad, yylineno);
        emit(tablesetelem, e, e->index, term, currQuad, yylineno);
        return term;
    }
    else {
        emit(op, e, newexpr_constint(1), e, currQuad, yylineno);
        expr* term = newexpr(arithexpr_e);
        term->sym = newtemp();
        emit(assign, e, NULL, term, currQuad, yylineno);
        return term;
    }
}

expr* do_not(expr* e) {
    expr* term = newexpr(boolexpr_e);
    term->sym = newtemp();
    emit(not_op, e, NULL, term, currQuad, yylineno);
    return term;
}

expr* do_var(char* name) {

    int ret_val = SymTable_insert(name, NO_LOCAL);

    if (ret_val == -4) {
        yyerror("No access to symbol");
        return newexpr(nil_e);
    }
    else if (ret_val == GLOBAL) {
        return lvalue_expr(SymTable_get_element_from_scope(name, 0));
    }
    else if (ret_val == NO_LOCAL) {
        SymbolTableEntry* element = SymTable_get_element_from_type(name, NO_LOCAL);

        if (element != NULL) {
            return lvalue_expr(element);
        }
        else {
            return lvalue_expr(SymTable_get_element_from_type(name, LOCAL));
        }
    }
    else if (ret_val == FORMAL) {
        return lvalue_expr(SymTable_get_element_from_type(name, FORMAL));
    }
    else if (ret_val == USERFUNC) {
        return lvalue_expr(SymTable_get_element_from_type(name, USERFUNC));
    }
    else if (ret_val == LIBFUNC) {
        return lvalue_expr(SymTable_get_element_from_type(name, LIBFUNC));
    }
    else {
        return lvalue_expr(SymTable_get_element_from_type(name, NO_LOCAL));
    }
}

expr* do_local_var(char* name) {

    if (curr_scope > 0) {
        int ret_val = SymTable_insert(name, LOCAL);

        if (ret_val == -2) {
            yyerror("Trying to shadow library function");
            return newexpr(nil_e);
        }
        else if (ret_val == NO_LOCAL) {
            SymbolTableEntry* element = SymTable_get_element_from_type(name, LOCAL);

            if (element) {
                return lvalue_expr(element);
            }

            element = SymTable_get_element_from_type(name, NO_LOCAL);
            if (element) {
                return lvalue_expr(SymTable_get_element_from_type(name, NO_LOCAL));
            }

            element = SymTable_get_element_from_type(name, FORMAL);
            if (element) {

                return lvalue_expr(SymTable_get_element_from_type(name, FORMAL));
            }
            else {
                return lvalue_expr(SymTable_get_element_from_type(name, USERFUNC));
            }
        }
        else {
            return lvalue_expr(SymTable_get_element_from_type(name, LOCAL));
        }
    }
    else {
        SymTable_insert(name, GLOBAL);
        return lvalue_expr(SymTable_get_element_from_scope(name, 0));
    }
}

expr* do_scope_var(char* name) {
    if (in_scope(name, 0)) {
        return lvalue_expr(SymTable_get_element_from_scope(name, 0));
    }
    else {
        yyerror("Global variable not found");
        return newexpr(nil_e);
    }
}

char* new_afunction() {
    char* an = malloc(100);
    sprintf(an, "$%d", anonymous++);
    return an;
}

expr* do_function(char* name) {

    int ret_val = SymTable_insert(name, USERFUNC);

    SymbolTableEntry* new_func = NULL;

    switch (ret_val) {
    case -2:
        yyerror("Shadowing library function is not allowed");
        break;

    case -3:
        yyerror("Redefining variables is not allowed");
        break;

    default:
        new_func = SymTable_get_element_from_type(name, USERFUNC);
        new_func->func_addr = currQuad;
        expr* new_lvalue = lvalue_expr(new_func);
        push_funclist(currQuad);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
        emit(funcstart, new_lvalue, NULL, NULL, currQuad, yylineno);

        save_func_offset();
        functionLocalOffset = 0;
        is_func++;

        return new_lvalue;
        break;
    }
}

expr* exit_func(expr* func, int locals) {

    is_func--;
    exit_scopespace();

    if (func->sym) {
        func->sym->total_locals = locals;
    }

    int offset = pop_and_top(stack_of_offsets);
    reset_functionlocal_offset(offset);

    while (return_list) {
        patchlabel(pop_returnlist(), currQuad);
    }

    emit(funcend, func, NULL, NULL, currQuad, yylineno);

    patchlabel(pop_funclist(), currQuad);
    return func;
}

expr* member_item(expr* lv, char* name) {
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

expr* array_item(expr* lv, expr* e) {
    if (lv)
        lv = emit_iftableitem(lv);
    else
        return newexpr_constnil();
    expr* new = newexpr(tableitem_e);
    new->sym = lv->sym;
    new->index = e;
};

expr* do_assign(expr* lv, expr* e) {

    if (lv && lv->type == tableitem_e) {

        emit(tablesetelem, lv, lv->index, e, currQuad, yylineno); 

        expr* assignexpr = emit_iftableitem(lv);
        assignexpr->type = assignexpr_e;
        return assignexpr;
    }
    else {

        emit(assign, e, NULL, lv, currQuad, yylineno);

        expr* assignexpr = newexpr(assignexpr_e);
        assignexpr->sym = newtemp();
        assignexpr->numConst = e->numConst;

        emit(assign, lv, NULL, assignexpr, currQuad, yylineno);

        return assignexpr;
    }
}

expr* make_call(expr* lv, expr* reversed_elist) {

    expr* func = emit_iftableitem(lv);
    reverse_list(reversed_elist);
    emit(call_op, func, NULL, NULL, currQuad, yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval, NULL, NULL, result, currQuad, yylineno);
    return result;
}

call* do_methodcall(char* id, expr* elist) {
    call* methodcall = (call*)malloc(sizeof(call));
    methodcall->elist = elist;
    methodcall->method = 1;
    methodcall->name = id;
    return methodcall;
}

call* do_normcall(expr* elist) {
    call* normcall = (call*)malloc(sizeof(call));
    normcall->elist = elist;
    normcall->method = 0;
    normcall->name = NULL;
    return normcall;
}

expr* do_lvalue_call(expr* lv, call* callsuffix) {

    lv = emit_iftableitem(lv);
    if (callsuffix->method) {
        expr* t = lv;
        lv = emit_iftableitem(member_item(t, callsuffix->name));
        callsuffix->elist = do_elist(t, callsuffix->elist);
    }
    expr* call = make_call(lv, callsuffix->elist);
    return call;
}

expr* do_funcdef_call(expr* funcdef, expr* elist) {
    expr* func = newexpr(programfunc_e);
    func->sym = funcdef->sym;
    expr* call = make_call(func, elist);
    return call;
}


expr* make_table(expr* elist) {
    expr* t = newexpr(newtable_e);
    t->sym = newtemp();
    emit(tablecreate, NULL, NULL, t, currQuad, yylineno);
    int i = 0;
    while (elist) {
        emit(tablesetelem, newexpr_constint(i++), elist, t, currQuad, yylineno);
        elist = elist->next;
    }
    return t;
}

expr* make_table_pairs(expr* indexed) {
    expr* t = newexpr(newtable_e);
    t->sym = newtemp();
    emit(tablecreate, NULL, NULL, t, currQuad, yylineno);
    while (indexed) {
        emit(tablesetelem, indexed->index, indexed->pair_value, t, currQuad, yylineno);
        indexed = indexed->next;
    }
    return t;
}

expr* make_indexedelem(expr* index, expr* pair_value) {
    expr* indexedelem = newexpr(tableitem_e);
    indexedelem->index = index;
    indexedelem->pair_value = pair_value;
    return indexedelem;
}

expr* make_indexedelem_list(expr* indexedelem, expr* indexedelem_list) {

    if (indexedelem_list) {
        indexedelem->next = indexedelem_list;
        return indexedelem;
    }
    else return indexedelem;
}


expr* do_par_funcdef(expr* funcdef) {
    expr* primary = newexpr(programfunc_e);
    primary->sym = funcdef->sym;
    return primary;
}

expr* do_elist(expr* e, expr* elistexpr_list) {

    if (elistexpr_list) {
        e->next = elistexpr_list;
        return e;
    }
    else return e;
}

stmt_t* do_break_continue(int arg) {
    if (loop_c <= 0)
        yyerror("Can't break/continue while not in loop");

    if (arg == 0) {
        stmt_t* statement = (stmt_t*)malloc(sizeof(stmt_t));
        make_stmt(statement);
        statement->breakList = newlist(nextquad());
        emit(jump, NULL, NULL, NULL, 0, yylineno);
        return statement;
    }
    else {
        stmt_t* statement = (stmt_t*)malloc(sizeof(stmt_t));
        make_stmt(statement);
        statement->contList = newlist(nextquad());
        emit(jump, NULL, NULL, NULL, 0, yylineno);
        return statement;
    }
}

int do_whilecond(expr* cond) {

    emit(if_eq, cond, newexpr_constbool(1), NULL, nextquad() + 2, yylineno);
    emit(jump, NULL, NULL, NULL, 0, yylineno);
    return nextquad() - 1;
}

void do_whilestmt(int whilestart, int whilecond, stmt_t* statement) {

    emit(jump, NULL, NULL, NULL, whilestart, yylineno);
    patchlabel(whilecond, nextquad());

    if (statement) {
        patchlist(statement->breakList, nextquad());
        patchlist(statement->contList, whilestart);
    }
}

for_pref* do_forprefix(int M, expr* e) {
    for_pref* fornode = (for_pref*)malloc(sizeof(for_pref));
    fornode->test = M;
    fornode->enter = nextquad();
    emit(if_eq, e, newexpr_constbool(1), NULL, 0, yylineno);
    return fornode;
}

void do_forstmt(for_pref* forprefix, int N1, int N2, stmt_t* statement, int N3) {
    --loop_c;
    if (forprefix) {
        patchlabel(forprefix->enter, N2 + 1);
        patchlabel(N1, nextquad());
        patchlabel(N2, forprefix->test);
        patchlabel(N3, N1 + 1);
    }
    if (statement) {
        patchlist(statement->breakList, nextquad());
        patchlist(statement->contList, N1 + 1);
    }
}

expr* do_relop(expr* expr1, expr* expr2, iopcode relop) {

    check_arith(expr1, "can't do relation operations on not arith value");
    check_arith(expr2, "can't do arithmetic operations on not arith value");

    expr* expr = newexpr(boolexpr_e);

    if (istempexpr(expr1)) {
        expr->sym = expr1->sym;
    }
    else if (istempexpr(expr2)) {
        expr->sym = expr2->sym;
    }
    else {
        expr->sym = newtemp();
    }

    emit(relop, expr1, expr2, NULL, nextquad() + 3, yylineno);
    emit(assign, newexpr_constbool(0), NULL, expr, nextquad(), yylineno);
    emit(jump, NULL, NULL, NULL, nextquad() + 2, yylineno);
    emit(assign, newexpr_constbool(1), NULL, expr, nextquad(), yylineno);

    return expr;
}

expr* do_boolop(expr* expr1, expr* expr2, iopcode boolop) {

    expr* expr = newexpr(boolexpr_e);

    if (istempexpr(expr1)) {
        expr->sym = expr1->sym;
    }
    else if (istempexpr(expr2)) {
        expr->sym = expr2->sym;
    }
    else {
        expr->sym = newtemp();
    }

    emit(boolop, expr1, expr2, expr, currQuad, yylineno);

    return expr;
}

int do_ifprefix(expr* e) {

    emit(if_eq, e, newexpr_constbool(1), NULL, nextquad() + 2, yylineno);
    emit(jump, NULL, NULL, NULL, 0, yylineno);
    return nextquad() - 1;
}


stmt_t* do_ifelse(stmt_t* ifstmt, stmt_t* elsestmt) {

    if (ifstmt && elsestmt) {

        if (elsestmt->breakList) {

            ifstmt->breakList = elsestmt->breakList;
        }

        if (elsestmt->contList) {

            ifstmt->contList = elsestmt->contList;
        }

        return ifstmt;
    }
    else if (ifstmt) {

        return ifstmt;
    }
    else {
        return elsestmt;
    }
}

expr* do_idlist(char* name) {

    int ret_val = SymTable_insert(name, FORMAL);

    switch (ret_val) {
    case -5:
        yyerror("Argument name already exists");
        break;

    case -2:
        yyerror("Argument trying to shadow library function");
        break;

    default:
        return lvalue_expr(SymTable_get_element_from_type(name, FORMAL));
        break;
    }
}

expr* do_moreID(char* name) {

    int ret_val = SymTable_insert(name, FORMAL);

    switch (ret_val) {
    case -5:
        yyerror("Argument name already exists");
        break;

    case -2:
        yyerror("Argument trying to shadow library function");
        break;

    default:
        return lvalue_expr(SymTable_get_element_from_type(name, FORMAL));
        break;
    }
}

stmt_t* do_stmtlist(stmt_t* stmt_list, stmt_t* stmt) {

    if (stmt_list && stmt) {
        stmt_t* stmts = (stmt_t*)malloc(sizeof(stmt_t));
        stmts->breakList = mergelist(stmt_list->breakList, stmt->breakList);
        stmts->contList = mergelist(stmt_list->contList, stmt->contList);
        return stmts;
    }
    else {
        if (!stmt_list) return stmt;
        else return stmt_list;
    }

    return NULL;
}


char* add_spaces(char* name, char* column) {

    char* temp_op = name;
    char* spaces = (char*)malloc(11 * sizeof(char));

    int op_len = strlen(column);
    int temp_op_len = strlen(temp_op);

    if (op_len > temp_op_len) {
        int j;
        for (j = 0; j < op_len - temp_op_len; j++) {
            spaces[j] = ' ';
        }
        spaces[j] = '\0';
        return spaces;
    }
    else {
        return NULL;

    }
}

void printArgs(expr* e, char* column) {

    if (e->type == var_e || e->type == programfunc_e || e->type == assignexpr_e || e->type == arithexpr_e || e->type == boolexpr_e || e->type == tableitem_e
        || e->type == newtable_e || e->type == libraryfunc_e) {
        char* spaces = add_spaces(e->sym->name, column);
        if (spaces == NULL) {
            printf("%s", e->sym->name);
        }
        else {
            printf("%s%s", spaces, e->sym->name);
        }
        free(spaces);
    }
    else if (e->type == constnum_e) {
        char buf[100];
        gcvt(e->numConst, 6, buf);
        char* spaces = add_spaces(buf, column);
        if (spaces == NULL) {
            printf("%s", buf);
        }
        else {
            printf("%s%s", spaces, buf);
        }
        free(spaces);
    }
    else if (e->type == nil_e) {
        char* spaces = add_spaces("NIL", column);
        if (spaces == NULL) {
            printf("%s", "NIL");
        }
        else {
            printf("%s%s", spaces, "NIL");
        }
        free(spaces);
    }
    else if (e->type == constbool_e) {
        if (e->boolConst == false) {
            char* spaces = add_spaces("FALSE", column);
            if (spaces == NULL) {
                printf("%s", "FALSE");
            }
            else {
                printf("%s%s", spaces, "FALSE");
            }
            free(spaces);
        }
        else {
            char* spaces = add_spaces("TRUE", column);
            if (spaces == NULL) {
                printf("%s", "TRUE");
            }
            else {
                printf("%s%s", spaces, "TRUE");
            }
            free(spaces);
        }
    }
    else if (e->type == conststring_e) {
        char* spaces = add_spaces(e->strConst, column);
        if (spaces == NULL) {
            printf("%s", e->strConst);
        }
        else {
            printf("%s%s", spaces, e->strConst);
        }
        free(spaces);
    }
}

void printQuads() {
    int i;
    printf("#  |     %s      |       %s       |     %s     |     %s     | %s | %s |\n", "Operation Opcode", "Results", "Argument_1", "Argument_2", "Label", "Line");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    char* str1 = malloc(100);
    char* str2 = malloc(100);

    for (i = 0; i < currQuad; i++) {

        if (i < 10) {
            printf("%d  ", i);
        }
        else if (i < 100) {
            printf("%d ", i);
        }
        else if (i < 1000) {
            printf("%d", i);
        }

        char* spaces = add_spaces(opcodes[quads[i].op], "Operation Opcode");
        if (spaces == NULL) {
            printf("      %s", opcodes[quads[i].op]);
        }
        else {
            printf("%s      %s", spaces, opcodes[quads[i].op]);
        }

        free(spaces);

        printf("              ");

        if (quads[i].result) {
            printArgs(quads[i].result, "Results");
        }
        else {

            printf("%s", "(empty)");
        }

        printf("             ");

        if (quads[i].arg1) {
            printArgs(quads[i].arg1, "Argument_1");
        }
        else {
            printf("   %s", "(empty)");
        }

        printf("           ");

        if (quads[i].arg2) {
            printArgs(quads[i].arg2, "Argument_2");
        }
        else {
            printf("   %s", "(empty)");
        }

        printf("       ");

        sprintf(str1, "%d", quads[i].label);

        if (quads[i].label != i) {

            char* spaces = add_spaces(str1, "Label");

            if (spaces == NULL) {
                printf("%s", str1);
            }
            else {
                printf("%s%s", spaces, str1);
            }

            free(spaces);
        }
        else {
            printf("    0");
        }

        printf("   ");

        if (quads[i].line == 0) {
            printf("   0");
        }
        else {
            sprintf(str2, "%d", quads[i].line);
            char* spaces = add_spaces(str2, "Line");
            if (!spaces) {
                printf("%s", str2);
            }
            else {
                printf("%s%s", spaces, str2);
            }
            free(spaces);
        }


        printf("\n");
    }

    free(str1);
    free(str2);
}