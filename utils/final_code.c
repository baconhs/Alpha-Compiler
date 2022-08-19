#include "final_code.h"

instruction** instructions = NULL;

incomplete_jump* ij_head = NULL;

extern quad* quads;

unsigned short umin = 0;

unsigned currInstr = 1;
unsigned total_instr = 1;

unsigned currprocessedquad;

extern double* numConsts;

extern unsigned totalNumConsts;

extern char** stringConsts;

extern unsigned totalStringConsts;

extern char** namedLibfuncs;

extern unsigned totalNamedLibfuncs;

extern struct userfunc** userFuncs;

extern unsigned totalUserFuncs;

extern FILE* yyout;

typedef void (*generator_func_t)(quad*);

void expandInstr() {
    assert(total_instr == nextinstructionlabel());
    instruction** i = malloc(NEW_INSTR_SIZE);
    if (instructions) {
        memcpy(i, instructions, CURR_INSTR_SIZE);
        free(instructions);
    }
    instructions = i;
    total_instr += EXPAND_SIZE;
}

void emitInstr(instruction* p) {
    if (currInstr == total_instr)
        expandInstr();
    instructions[currInstr++] = p;
}

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_JUMP,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM };

int nextinstructionlabel() {
    return currInstr;
}

void make_operand(expr* e, vmarg* arg) {
    if (!e)
        return;

    switch (e->type) {

    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case assignexpr_e:
    case newtable_e:
    {
        assert(e->sym);
        arg->val = e->sym->offset;

        switch (e->sym->space) {
        case programvar:
            arg->type = global_a;
            break;
        case functionlocal:
            arg->type = local_a;
            break;
        case formalarg:
            arg->type = formal_a;
            break;
        default:
            assert(0);
        }
        break;
    }

    case programfunc_e:
    {
        arg->type = userfunc_a;
        arg->val = userfuncs_newfunc(e->sym);
        break;
    }

    case libraryfunc_e:
    {
        arg->type = libfunc_a;
        arg->val = libfuncs_newused(e->sym->name);
        break;
    }

    case constnum_e:
    {
        arg->val = consts_newnumber(e->numConst);
        arg->type = number_a;
        break;
    }

    case constbool_e:
    {
        arg->val = e->boolConst;
        arg->type = bool_a;
        break;
    }

    case conststring_e:
    {
        arg->val = consts_newstring(e->strConst);
        arg->type = string_a;
        break;
    }

    default:
        assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val) {
    arg->val = val;
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val) {
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg) {
    arg->type = retval_a;
}

void generator() {

    for (unsigned int i = 0; i < nextquad(); i++) {
        currprocessedquad = i;
        (*generators[quads[i].op])(quads + i);
    }
    patch_incomplete_jump();
    make_text_file();
    make_bin_file();
}

void generate(vmopcode op, quad* quad) {
    instruction* t = malloc(sizeof(instruction));

    t->opcode = op;
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    t->srcLine = quad->line;

    make_operand(quad->arg1, t->arg1);

    if (umin) {
        make_operand(newexpr_constint(-1), t->arg2);
    }
    else {
        make_operand(quad->arg2, t->arg2);
    }

    if (!t->arg2->type && !t->arg2->val) {
        t->arg2 = NULL;
    }

    make_operand(quad->result, t->result);

    quad->taddress = nextinstructionlabel();

    emitInstr(t);
}

void add_incomplete_jump(unsigned instr, unsigned jump_dest) {

    incomplete_jump* jump = malloc(sizeof(incomplete_jump));
    jump->instrNo = instr;
    jump->iaddress = jump_dest;
    jump->next = NULL;

    if (!ij_head) {
        ij_head = jump;
    }
    else {
        incomplete_jump* temp_curr = ij_head;
        while (temp_curr->next != NULL) {
            temp_curr = temp_curr->next;
        }
        temp_curr->next = jump;
    }
}

void generate_relational(vmopcode op, quad* quad) {

    instruction* t = malloc(sizeof(instruction));

    if (op != jump_v) {
        t->arg1 = malloc(sizeof(vmarg));
        t->arg2 = malloc(sizeof(vmarg));
        make_operand(quad->arg1, t->arg1);
        make_operand(quad->arg2, t->arg2);
    }
    else {
        t->arg1 = NULL;
        t->arg2 = NULL;
    }

    t->result = calloc(1, sizeof(vmarg));
    t->opcode = op;
    t->srcLine = quad->line;

    t->result->type = label_a;
    if (quad->label < currprocessedquad) {
        t->result->val = quads[quad->label].taddress;
    }
    else {
        add_incomplete_jump(nextinstructionlabel(), quad->label);
    }
    quad->taddress = nextinstructionlabel();
    emitInstr(t);
}

void generate_ADD(quad* quad) { generate(add_v, quad); }

void generate_SUB(quad* quad) { generate(sub_v, quad); }

void generate_MUL(quad* quad) { generate(mul_v, quad); }

void generate_UMINUS(quad* quad) {
    umin = 1;
    generate(mul_v, quad);
    umin = 0;
}

void generate_DIV(quad* quad) { generate(div_v, quad); }

void generate_MOD(quad* quad) { generate(mod_v, quad); }

void generate_NEWTABLE(quad* quad) { generate(newtable_v, quad); }

void generate_TABLEGETELEM(quad* quad) { generate(tablegetelem_v, quad); }

void generate_TABLESETELEM(quad* quad) { generate(tablesetelem_v, quad); }

void generate_ASSIGN(quad* quad) { generate(assign_v, quad); }

void generate_JUMP(quad* quad) { generate_relational(jump_v, quad); }

void generate_IF_EQ(quad* quad) { generate_relational(jeq_v, quad); }

void generate_IF_NOTEQ(quad* quad) { generate_relational(jne_v, quad); }

void generate_IF_GREATER(quad* quad) { generate_relational(jgt_v, quad); }

void generate_IF_GREATEREQ(quad* quad) { generate_relational(jge_v, quad); }

void generate_IF_LESS(quad* quad) { generate_relational(jlt_v, quad); }

void generate_IF_LESSEQ(quad* quad) { generate_relational(jle_v, quad); }

void generate_NOT(quad* quad) {

    quad->taddress = nextinstructionlabel();

    instruction* t = malloc(sizeof(instruction));
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    t->opcode = jeq_v;
    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, false);
    t->result->type = label_a;
    t->result->val = nextinstructionlabel() + 3;
    emitInstr(t);

    instruction* t1 = malloc(sizeof(instruction));
    t1->arg1 = malloc(sizeof(vmarg));
    t1->arg2 = NULL;
    t1->result = malloc(sizeof(vmarg));
    t1->opcode = assign_v;
    make_booloperand(t1->arg1, false);
    make_operand(quad->result, t1->result);
    emitInstr(t1);

    instruction* t2 = malloc(sizeof(instruction));
    t2->arg1 = NULL;
    t2->arg2 = NULL;
    t2->result = malloc(sizeof(vmarg));
    t2->opcode = jump_v;
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel() + 2;

    emitInstr(t2);

    instruction* t3 = malloc(sizeof(instruction));
    t3->arg1 = malloc(sizeof(vmarg));
    t3->arg2 = NULL;
    t3->result = malloc(sizeof(vmarg));
    t3->opcode = assign_v;
    make_booloperand(t3->arg1, true);
    make_operand(quad->result, t3->result);
    emitInstr(t3);
}

void generate_OR(quad* quad) {

    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    t->opcode = jeq_v;
    t->srcLine = quad->line;

    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, true);
    t->result->type = label_a;
    t->result->val = nextinstructionlabel() + 4;
    emitInstr(t);

    instruction* t2 = malloc(sizeof(instruction));
    t2->arg1 = malloc(sizeof(vmarg));
    t2->arg2 = malloc(sizeof(vmarg));
    t2->result = malloc(sizeof(vmarg));
    t2->srcLine = quad->line;
    t2->opcode = jeq_v;

    make_operand(quad->arg2, t2->arg1);
    make_booloperand(t2->arg2, true);
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel() + 3;
    emitInstr(t2);

    instruction* t3 = malloc(sizeof(instruction));
    t3->arg1 = malloc(sizeof(vmarg));
    t3->arg2 = NULL;
    t3->result = malloc(sizeof(vmarg));
    t3->srcLine = quad->line;
    t3->opcode = assign_v;

    make_booloperand(t3->arg1, false);
    make_operand(quad->result, t3->result);
    emitInstr(t3);

    instruction* t4 = malloc(sizeof(instruction));
    t4->arg1 = NULL;
    t4->arg2 = NULL;
    t4->result = malloc(sizeof(vmarg));
    t4->srcLine = quad->line;
    t4->opcode = jump_v;
    t4->result->type = label_a;
    t4->result->val = nextinstructionlabel() + 2;
    emitInstr(t4);

    instruction* t5 = malloc(sizeof(instruction));
    t5->arg1 = malloc(sizeof(vmarg));
    t5->arg2 = NULL;
    t5->result = malloc(sizeof(vmarg));
    t5->srcLine = quad->line;
    t5->opcode = assign_v;

    make_booloperand(t5->arg1, true);
    make_operand(quad->result, t5->result);
    emitInstr(t5);
}

void generate_AND(quad* quad) {

    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->arg1 = malloc(sizeof(vmarg));
    t->arg2 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    t->opcode = jeq_v;
    t->srcLine = quad->line;

    make_operand(quad->arg1, t->arg1);
    make_booloperand(t->arg2, false);
    t->result->type = label_a;
    t->result->val = nextinstructionlabel() + 4;
    emitInstr(t);

    instruction* t2 = malloc(sizeof(instruction));
    t2->arg1 = malloc(sizeof(vmarg));
    t2->arg2 = malloc(sizeof(vmarg));
    t2->result = malloc(sizeof(vmarg));
    t2->srcLine = quad->line;
    t2->opcode = jeq_v;

    make_operand(quad->arg2, t2->arg1);
    make_booloperand(t2->arg2, false);
    t2->result->type = label_a;
    t2->result->val = nextinstructionlabel() + 3;
    emitInstr(t2);

    instruction* t3 = malloc(sizeof(instruction));
    t3->arg1 = malloc(sizeof(vmarg));
    t3->arg2 = NULL;
    t3->result = malloc(sizeof(vmarg));
    t3->srcLine = quad->line;
    t3->opcode = assign_v;

    make_booloperand(t3->arg1, true);
    make_operand(quad->result, t3->result);
    emitInstr(t3);

    instruction* t4 = malloc(sizeof(instruction));
    t4->arg1 = NULL;
    t4->arg2 = NULL;
    t4->result = malloc(sizeof(vmarg));
    t4->srcLine = quad->line;
    t4->opcode = jump_v;

    t4->result->type = label_a;
    t4->result->val = nextinstructionlabel() + 2;
    emitInstr(t4);

    instruction* t5 = malloc(sizeof(instruction));
    t5->arg1 = malloc(sizeof(vmarg));
    t5->arg2 = NULL;
    t5->result = malloc(sizeof(vmarg));
    t5->srcLine = quad->line;
    t5->opcode = assign_v;

    make_booloperand(t5->arg1, false);
    make_operand(quad->result, t5->result);
    emitInstr(t5);
}

void generate_PARAM(quad* quad) {

    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->result = malloc(sizeof(vmarg));
    t->opcode = pusharg_v;
    t->srcLine = quad->line;

    make_operand(quad->arg1, t->result);
    emitInstr(t);
}

void generate_CALL(quad* quad) {

    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->result = malloc(sizeof(vmarg));
    t->opcode = call_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, t->result);
    emitInstr(t);
}

void generate_GETRETVAL(quad* quad) {
    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->arg1 = malloc(sizeof(vmarg));
    t->result = malloc(sizeof(vmarg));
    t->opcode = assign_v;
    t->srcLine = quad->line;
    make_operand(quad->result, t->result);
    make_retvaloperand(t->arg1); 
    emitInstr(t);
}

void generate_RETURN(quad* quad) { 
    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->result = malloc(sizeof(vmarg));
    t->opcode = assign_v;
    t->arg1 = malloc(sizeof(vmarg));
    t->srcLine = quad->line;

    make_retvaloperand(t->result);
    make_operand(quad->arg1, t->arg1);
    emitInstr(t);
}

void generate_FUNCSTART(quad* quad) { 

    quad->taddress = nextinstructionlabel();
    quad->arg1->sym->func_addr = nextinstructionlabel();

    instruction* t = malloc(sizeof(instruction));
    t->result = malloc(sizeof(vmarg));

    t->opcode = funcenter_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, t->result);
    emitInstr(t);
}



void generate_FUNCEND(quad* quad) { 
    quad->taddress = nextinstructionlabel();
    instruction* t = malloc(sizeof(instruction));
    t->result = malloc(sizeof(vmarg));
    t->opcode = funcexit_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, t->result);
    emitInstr(t);
}

unsigned consts_newnumber(double n) {

    for (unsigned int i = 0; i < totalNumConsts; i++) {
        if (numConsts[i] == n) {
            return i;
        }
    }

    totalNumConsts++;

    if (numConsts) {
        numConsts = realloc(numConsts, totalNumConsts * sizeof(double));
        numConsts[totalNumConsts - 1] = n;
    }
    else {
        numConsts = malloc(totalNumConsts * sizeof(double));
        numConsts[0] = n;
    }

    return totalNumConsts - 1;
}

unsigned libfuncs_newused(char* s) {
    for (unsigned int i = 0; i < totalNamedLibfuncs; i++) {
        if (strcmp(namedLibfuncs[i], s) == 0) {
            return i;
        }
    }

    totalNamedLibfuncs++;

    if (namedLibfuncs) {
        namedLibfuncs = realloc(namedLibfuncs, totalNamedLibfuncs * sizeof(char*));
        namedLibfuncs[totalNamedLibfuncs - 1] = s;
    }
    else {
        namedLibfuncs = malloc(totalNamedLibfuncs * sizeof(char*));
        namedLibfuncs[0] = s;
    }

    return totalNamedLibfuncs - 1;
}

unsigned userfuncs_newfunc(SymbolTableEntry* sym) {
    for (unsigned int i = 0; i < totalUserFuncs; i++) {
        if (userFuncs[i]->address == sym->func_addr) {
            return i;
        }
    }

    totalUserFuncs++;
    if (userFuncs) {
        userFuncs = realloc(userFuncs, totalUserFuncs * sizeof(userfunc*));
        userFuncs[totalUserFuncs - 1] = malloc(sizeof(userfunc));
        userFuncs[totalUserFuncs - 1]->address = sym->func_addr;
        userFuncs[totalUserFuncs - 1]->localSize = sym->total_locals;
        userFuncs[totalUserFuncs - 1]->id = sym->name;
    }
    else {
        userFuncs = malloc(totalUserFuncs * sizeof(userfunc*));
        userFuncs[0] = malloc(sizeof(userfunc));
        userFuncs[0]->address = sym->func_addr;
        userFuncs[0]->localSize = sym->total_locals;
        userFuncs[0]->id = sym->name;
    }

    return totalUserFuncs - 1;
}

unsigned consts_newstring(char* s) {
    for (unsigned int i = 0; i < totalStringConsts; i++) {
        if (strcmp(stringConsts[i], s) == 0) {
            return i;
        }
    }

    totalStringConsts++;

    if (stringConsts) {
        stringConsts = realloc(stringConsts, totalStringConsts * sizeof(char*));
        stringConsts[totalStringConsts - 1] = s;
    }
    else {
        stringConsts = malloc(totalStringConsts * sizeof(char*));
        stringConsts[0] = s;
    }

    return totalStringConsts - 1;
}

void patch_incomplete_jump() {

    incomplete_jump* temp = ij_head;

    while (temp != NULL) {

        instructions[temp->instrNo]->result->type = label_a;

        if ((temp->iaddress != nextquad())) {
            instructions[temp->instrNo]->result->val = quads[temp->iaddress].taddress;
        }
        else {
            instructions[temp->instrNo]->result->val = currInstr;
        }
        temp = temp->next;
    }
}

void make_bin_file() {
    char* magic_number = MAGIC_NUMBER;
    FILE* fp = fopen("alpha_bin.abc", "wb");
    if (!fp) {
        exit(1);
    }
    fwrite(magic_number, strlen(magic_number), 1, fp);

    fwrite(&totalStringConsts, sizeof(totalStringConsts), 1, fp);
    for (unsigned i = 0; i < totalStringConsts; i++) {
        int str_const_len = strlen(stringConsts[i]);
        fwrite(&str_const_len, sizeof(int), 1, fp);
        fwrite(stringConsts[i], strlen(stringConsts[i]), 1, fp);
    }

    fwrite(&totalNumConsts, sizeof(totalNumConsts), 1, fp);
    for (unsigned i = 0; i < totalNumConsts; i++) {
        fwrite(&numConsts[i], sizeof(numConsts[i]), 1, fp);
    }

    fwrite(&totalUserFuncs, sizeof(totalUserFuncs), 1, fp);
    for (unsigned i = 0; i < totalUserFuncs; i++) {
        int func_id_len = strlen(userFuncs[i]->id);
        fwrite(&func_id_len, sizeof(int), 1, fp);
        fwrite(&userFuncs[i]->address, sizeof(int), 1, fp);
        fwrite(&userFuncs[i]->localSize, sizeof(int), 1, fp);
        fwrite(userFuncs[i]->id, strlen(userFuncs[i]->id), 1, fp);
    }

    fwrite(&totalNamedLibfuncs, sizeof(totalNamedLibfuncs), 1, fp);
    for (unsigned i = 0; i < totalNamedLibfuncs; i++) {
        int lib_func_len = strlen(namedLibfuncs[i]);
        fwrite(&lib_func_len, sizeof(int), 1, fp);
        fwrite(namedLibfuncs[i], strlen(namedLibfuncs[i]), 1, fp);
    }

    fwrite(&currInstr, sizeof(currInstr), 1, fp);

    for (unsigned i = 1; i < currInstr; i++) {
        fwrite(&instructions[i]->opcode, sizeof(vmarg_t), 1, fp);

        if (instructions[i]->result) {

            fwrite(&instructions[i]->result->type, sizeof(vmarg_t), 1, fp);
            fwrite(&instructions[i]->result->val, sizeof(int), 1, fp);
        }
        int zero = 0;
        if (instructions[i]->arg1) {
            fwrite(&instructions[i]->arg1->type, sizeof(vmarg_t), 1, fp);
            fwrite(&instructions[i]->arg1->val, sizeof(int), 1, fp);
        }
        else {
            fwrite(&zero, sizeof(vmarg_t), 1, fp);
            fwrite(&zero, sizeof(int), 1, fp);
        }

        if (instructions[i]->arg2) {
            fwrite(&instructions[i]->arg2->type, sizeof(vmarg_t), 1, fp);
            fwrite(&instructions[i]->arg2->val, sizeof(int), 1, fp);
        }
        else {
            fwrite(&zero, sizeof(vmarg_t), 1, fp);
            fwrite(&zero, sizeof(int), 1, fp);
        }
        fwrite(&instructions[i]->srcLine, sizeof(int), 1, fp);
    }
}

void printInstructionArgs(FILE* fp, vmarg* vma, int temp_spaces) {

    if (vma->type == global_a || vma->type == formal_a || vma->type == local_a || vma->type == bool_a) {
        int i = 0, space = 1, total_space = temp_spaces;
        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (vma->val != 0) {
            space += floor(log10(abs(vma->val))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%d", vma->type, vma->val);
    }
    else if (vma->type == number_a) {
        int i = 0, space = 1, total_space = temp_spaces;
        char str[100];
        sprintf(str, "%g", numConsts[vma->val]);
        space += strlen(str);

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%g", vma->type, numConsts[vma->val]);
    }
    else if (vma->type == nil_a) {

        int i = 0, space = 0, total_space = temp_spaces;

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d", vma->type);
    }
    else if (vma->type == string_a) {

        int i = 0, space = 1, total_space = temp_spaces;

        space += strlen(stringConsts[vma->val]);

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }

        fprintf(fp, "%d:%s", vma->type, stringConsts[vma->val]);
    }
    else if (vma->type == userfunc_a) {

        int i = 0, space = 2, total_space = temp_spaces;

        space += strlen(userFuncs[vma->val]->id);

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (vma->val != 0) {
            space += floor(log10(abs(vma->val))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%s %d", vma->type, userFuncs[vma->val]->id, vma->val);
    }
    else if (vma->type == libfunc_a) {

        int i = 0, space = 1, total_space = temp_spaces;

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        space += strlen(namedLibfuncs[vma->val]);

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%s", vma->type, namedLibfuncs[vma->val]);
    }
    else if (vma->type == label_a) {

        int i = 0, space = 1, total_space = temp_spaces;

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (vma->val != 0) {
            space += floor(log10(abs(vma->val))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%d", vma->type, vma->val);
    }
    else if (vma->type == retval_a) {

        int i = 0, space = 1, total_space = temp_spaces;

        if (vma->type != 0) {
            space += floor(log10(abs(vma->type))) + 1;
        }
        else {
            space += 1;
        }

        if (vma->val != 0) {
            space += floor(log10(abs(vma->val))) + 1;
        }
        else {
            space += 1;
        }

        if (total_space > space) {
            for (i; i < total_space - space; i++) {

                fprintf(fp, " ");
            }
        }
        fprintf(fp, "%d:%d", vma->type, vma->val);
    }
}

void make_text_file() {
    char* magic_number = MAGIC_NUMBER;
    FILE* fp = fopen("tcode_text.abc", "w");

    if (fp) {
        fprintf(fp, "Magic number is: %s\n\n", magic_number);

        fprintf(fp, "The total number consts are %u:\n\n", totalNumConsts);
        for (unsigned i = 0; i < totalNumConsts; i++) {
            fprintf(fp, "%g\n", numConsts[i]);
        }

        fprintf(fp, "\nThe total string consts are %d:\n\n", totalStringConsts);

        for (unsigned i = 0; i < totalStringConsts; i++) {
            fprintf(fp, "Length: %u Value: %s\n", strlen(stringConsts[i]), stringConsts[i]);
        }

        fprintf(fp, "\nThe total user functions are %u:\n\n", totalUserFuncs);
        for (unsigned i = 0; i < totalUserFuncs; i++) {
            fprintf(fp, "address:%d size:%d name: %s\n", userFuncs[i]->address, userFuncs[i]->localSize, (userFuncs[i]->id));
        }

        fprintf(fp, "\nThe total library functions are %u:\n\n", totalNamedLibfuncs);

        for (unsigned i = 0; i < totalNamedLibfuncs; i++) {
            fprintf(fp, "%u %s\n", strlen(namedLibfuncs[i]), namedLibfuncs[i]);
        }

        fprintf(fp, "\nThe total instructions are %d:\n", currInstr - 1);

        int i;
        fprintf(fp, "\n#  |  %s   |  %s  |  %s  |  %s  | %s |\n", "Opcode", "Results", "Argument_1", "Argument_2", "Line");
        fprintf(fp, "-----------------------------------------------------------------\n");
        for (i = 1; i < nextinstructionlabel(); i++) {
            if (i < 10) {
                fprintf(fp, "%d  ", i);
            }
            else if (i < 100) {
                fprintf(fp, "%d ", i);
            }
            else if (i < 1000) {
                fprintf(fp, "%d", i);
            }

            if (instructions[i]->opcode < 10) {
                fprintf(fp, "        %d", instructions[i]->opcode);
            }
            else {
                fprintf(fp, "       %d", instructions[i]->opcode);
            }
            if (instructions[i]->result) {
                printInstructionArgs(fp, instructions[i]->result, 13);
            }
            else {
                fprintf(fp, "      %s", "(empty)");
            }
            if (instructions[i]->arg1) {
                printInstructionArgs(fp, instructions[i]->arg1, 15);
            }
            else {
                fprintf(fp, "        %s", "(empty)");
            }

            if (instructions[i]->arg2) {
                printInstructionArgs(fp, instructions[i]->arg2, 15);
            }
            else {
                fprintf(fp, "        %s", "(empty)");
            }

            if (instructions[i]->srcLine < 10) {
                fprintf(fp, "       %d", instructions[i]->srcLine);
            }
            else if (instructions[i]->srcLine < 100) {
                fprintf(fp, "      %d ", instructions[i]->srcLine);
            }
            else if (instructions[i]->srcLine < 1000) {
                fprintf(fp, "     %d", instructions[i]->srcLine);
            }
            else {
                fprintf(fp, "    %d", instructions[i]->srcLine);
            }
            fprintf(fp, "\n");
        }
    }

    else {
        exit(1);
    }
}