#ifndef VM_H
#define VM_H

#include "utils.h"
#include "final_code.h"


#define AVM_STACKENV_SIZE 4
#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&m, 0, sizeof(m));
#define AVM_TABLE_HASHSIZE 211
#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_ENDING_PC codeSize
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define AVM_SAVEDPC_OFFSET +3
#define AVM_NUMACTUALS_OFFSET +4



#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_compare
#define execute_jge execute_compare
#define execute_jlt execute_compare
#define execute_jgt execute_compare

typedef enum avm_memcell_t {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
} avm_memcell_t;

typedef struct avm_table avm_table;

typedef struct avm_memcell {
    enum avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
} avm_memcell;

typedef struct avm_table_bucket {
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
} avm_table_bucket;

typedef struct avm_table {
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
}avm_table;

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_tableincrefcounter(avm_table* t);

void memclear_table(avm_memcell* m);

void avm_tabledecrefcounter(avm_table* t);

void avm_tablebucketsinit(avm_table_bucket** p);

void avm_tablebucketsdestroy(avm_table_bucket** p);

void avm_tabledestroy(avm_table* t);

avm_table* avm_tablenew(void);

double consts_getnumber(unsigned index);

char* consts_getstring(unsigned index);

char* libfuncs_getused(unsigned index);

unsigned funcs_get_address(unsigned index);

userfunc* funcs_get(unsigned index);

void avm_memcellclear(avm_memcell* m);

void memclear_string(avm_memcell* m);

void avm_warning(char* format);

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void execute_assign(instruction* instr);

void avm_error(char* format);

char* avm_tostring(avm_memcell*);

void avm_calllibfunc(char* funcName);

void avm_callsaveenviroment(void);

void execute_call(instruction* instr);

void avm_dec_top(void);

void avm_push_envvalue(unsigned val);

userfunc* avm_getfuncinfo(unsigned address);

void excecute_funcecnter(instruction* instr);

unsigned avm_get_envvalue(unsigned i);

typedef void (*library_func_t)(void);

library_func_t avm_getlibraryfunc(char* id);

unsigned avm_totalactuals(void);

avm_memcell* avm_getactual(unsigned i);

void libfunc_print(void);

void avm_registerlibfunc(char* id, library_func_t addr);

char* number_tostring(avm_memcell*);

char* string_tostring(avm_memcell*);

char* bool_tostring(avm_memcell*);

char* table_tostring(avm_memcell*);

char* userfunc_tostring(avm_memcell*);

char* libfunc_tostring(avm_memcell*);

void libfunc_argument(void);

char* nil_tostring(avm_memcell*);

char* undef_tostring(avm_memcell*);

avm_memcell* avm_tablegetelem(avm_table* talbe, avm_memcell* index);

void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content);

void execute_pusharg(instruction* instr);

void excecute_newtable(instruction* instr);

void execute_tablegetelem(instruction* instr);

void execute_tablesetelem(instruction* instr);

void execute_compare(instruction* instr);

void execute_arithmetic(instruction* instr);

void execute_assign(instruction* instr);
void execute_add(instruction* instr);
void execute_sub(instruction* instr);
void execute_mul(instruction* instr);
void execute_div(instruction* instr);
void execute_mod(instruction* instr);
void execute_uminus(instruction* instr);
void execute_and(instruction* instr);
void execute_or(instruction* instr);
void execute_not(instruction* instr);
void execute_jeq(instruction* instr);
void execute_jne(instruction* instr);
void execute_jle(instruction* instr);
void execute_jge(instruction* instr);
void execute_jlt(instruction* instr);
void execute_jgt(instruction* instr);
void execute_jump(instruction* instr);
void execute_call(instruction* instr);
void execute_pusharg(instruction* instr);
void execute_funcenter(instruction* instr);
void execute_funcexit(instruction* instr);
void execute_newtable(instruction* instr);
void execute_tablegetelem(instruction* instr);
void execute_tablesetelem(instruction* instr);

void execute_cycle(void);

double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);


unsigned char number_tobool(avm_memcell* m);
unsigned char string_tobool(avm_memcell* m);
unsigned char bool_tobool(avm_memcell* m);
unsigned char table_tobool(avm_memcell* m);
unsigned char userfunc_tobool(avm_memcell* m);
unsigned char libfunc_tobool(avm_memcell* m);
unsigned char nil_tobool(avm_memcell* m);
unsigned char undef_tobool(avm_memcell* m);
unsigned char avm_tobool(avm_memcell* m);

void libfunc_typeof();

void avm_initialize(void);

void libfunc_totalarguments(void);

char* string_tostring(avm_memcell* m);

char* number_tostring(avm_memcell* m);

void avm_initstack(void);

void add_vm_instr(instruction* instr, int i);

void read_bin_file();

int start_avm();

unsigned le(double x, double y);

unsigned ge(double x,double y);

unsigned lt(double x, double y);

unsigned gt(double x, double y);

void setGlobals(unsigned offset);


#endif