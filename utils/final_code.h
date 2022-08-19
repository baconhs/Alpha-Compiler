#ifndef FINAL_CODE_H
#define FINAL_CODE_H

#include "symtable.h"
#include "utils.h"
#include <assert.h>
#include <math.h>

#define CURR_INSTR_SIZE   (total_instr * sizeof(instruction *))
#define NEW_INSTR_SIZE    (EXPAND_SIZE * sizeof(instruction *) + CURR_INSTR_SIZE)
#define MAGIC_NUMBER "340200501"

typedef struct incomplete_jump {
    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump* next;
} incomplete_jump;

typedef enum vmopcode {
    assign_v, add_v, sub_v,
    mul_v, div_v, mod_v,
    uminus_v, and_v, or_v,
    not_v, jeq_v, jne_v,
    jle_v, jge_v, jlt_v,
    jgt_v, jump_v, call_v,
    pusharg_v, funcenter_v, funcexit_v,
    newtable_v, tablegetelem_v, tablesetelem_v, nop_v
} vmopcode;

typedef enum vmarg_t {
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a
}  vmarg_t;

typedef struct vmarg {
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction {
    vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned srcLine;
} instruction;

typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    char* id;
} userfunc;

unsigned consts_newstring(char* s);

unsigned consts_newnumber(double n);

unsigned libfuncs_newused(char* s);

unsigned userfuncs_newfunc(SymbolTableEntry* sym);

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);

int nextinstructionlabel();

void make_operand(expr* e, vmarg* arg);

void make_numberoperand(vmarg* arg, double val);

void make_booloperand(vmarg* arg, unsigned val);

void make_retvaloperand(vmarg* arg);

void generator();

void generate(vmopcode op, quad* quad);

void generate_relational(vmopcode op, quad* quad);

void generate_ADD(quad* quad);

void generate_SUB(quad* quad);

void generate_MUL(quad* quad);

void generate_UMINUS(quad* quad);

void generate_DIV(quad* quad);

void generate_MOD(quad* quad);

void generate_NEWTABLE(quad* quad);

void generate_TABLEGETELEM(quad* quad);

void generate_TABLESETELEM(quad* quad);

void generate_ASSIGN(quad* quad);

void generate_JUMP(quad* quad);

void generate_IF_EQ(quad* quad);

void generate_IF_NOTEQ(quad* quad);

void generate_IF_GREATER(quad* quad);

void generate_IF_GREATEREQ(quad* quad);

void generate_IF_LESS(quad* quad);

void generate_IF_LESSEQ(quad* quad);

void generate_NOT(quad* quad);

void generate_AND(quad* quad);

void generate_OR(quad* quad);

void generate_AND(quad* quad);

void generate_PARAM(quad* quad);

void generate_CALL(quad* quad);

void generate_GETRETVAL(quad* quad);

void generate_FUNCSTART(quad* quad);

void generate_RETURN(quad* quad);

void generate_FUNCEND(quad* quad);

void emitInstr(instruction* t);

void expandInstr();

void patch_incomplete_jump();

void printInstructionArgs(FILE* fp,vmarg* vma, int temp_spaces);

void printInstructions();

vmarg* reset_operand(vmarg* arg);

void make_text_file();

void make_bin_file();

#endif