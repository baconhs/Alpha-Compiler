#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include "symtable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)


typedef enum iopcode {
    assign,
    add,
    sub,
    mul,
    div_op,
    mod,
    uminus,
    and_op,
    or_op,
    not_op,
    if_eq,
    if_noteq,
    if_lesseq,
    if_greatereq,
    if_less,
    if_greater,
    jump,
    call_op,
    param,
    ret,
    getretval,
    funcstart,
    funcend,
    tablecreate,
    tablegetelem,
    tablesetelem
} iopcode;

typedef enum expr_t {
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e,
} expr_t;

typedef struct expr {
    expr_t type;
    SymbolTableEntry* sym;
    int falseList;
    int trueList;
    struct expr* index;
    struct expr* pair_value;
    double numConst;
    char* strConst;
    bool boolConst;
    struct expr* next;
} expr;

typedef struct call {
    expr* elist;
    unsigned char method;
    char* name;
} call;

typedef struct funclist {
    int label;
    struct funclist* prev;
}funclist;

typedef struct returnlist {
    int label;
    struct returnlist* prev;
}returnlist;


typedef struct quad {
    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned int label;
    unsigned int line;
    unsigned taddress;
} quad;

typedef struct stmt_t {
    int breakList, contList;
} stmt_t;

typedef struct for_pref {
    unsigned int enter, test;
} for_pref;

void make_stmt(stmt_t* s);

int newlist(int i);

int mergelist(int l1, int l2);

void patchlist(int list, int label);

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned int label, unsigned int line);

void expand();

expr* emit_iftableitem(expr* e);

SymbolTableEntry* newtemp();

char* newtempname();

void check_arith(expr* e, char* context);

unsigned int istempexpr(expr* e);

expr* newexpr(expr_t type);

expr* newexpr_constnum(double i);

expr* newexpr_constint(int i);

expr* newexpr_constbool(unsigned int b);

expr* newexpr_conststring(char* str);

expr* newexpr_constnil();

expr* lvalue_expr(SymbolTableEntry* sym);

void patchlabel(unsigned quadNo, unsigned label);

unsigned nextquad(void);

void reset_functionlocal_offset(int offset);

void reverse_list(expr* reversed_elist);

int yyerror(const char* message);

expr* do_op(expr* arg1, expr* arg2, iopcode op);

expr* do_uminus(expr* e);

expr* do_post_dec_inc(expr* e, iopcode op);

expr* do_pre_dec_inc(expr* e, iopcode op);

expr* do_not(expr* e);

expr* do_var(char* name);

expr* do_local_var(char* name);

expr* do_scope_var(char* name);

SymbolTableEntry* check_for_temp(expr* arg1, expr* arg2);

char* new_afunction();

expr* do_function(char* name);

expr* exit_func(expr* func, int locals);

expr* member_item(expr* lv, char* name);

expr* array_item(expr* lv, expr* e);

expr* do_assign(expr* lv, expr* e);

expr* make_call(expr* lv, expr* reversed_elist);

call* do_methodcall(char* id, expr* elist);

call* do_normcall(expr* elist);

expr* do_lvalue_call(expr* lv, call* callsuffix);

expr* do_funcdef_call(expr* funcdef, expr* elist);

expr* make_table(expr* elist);

expr* make_table_pairs(expr* elist);

expr* make_indexedelem(expr* index, expr* pair_value);

expr* make_indexedelem_list(expr* indexedelem, expr* indexedelem_list);

expr* do_par_funcdef(expr* funcdef);

expr* do_elist(expr* e, expr* elistexpr_list);

stmt_t* do_break_continue(int arg);

int do_whilecond(expr* cond);

void do_whilestmt(int whilestart, int whilecond, stmt_t* statement);

for_pref* do_forprefix(int M, expr* e);

void do_forstmt(for_pref* forprefix, int N1, int N2, stmt_t* statement, int N3);

expr* do_relop(expr* expr1, expr* expr2, iopcode relop);

expr* do_boolop(expr* expr1, expr* expr2, iopcode boolop);

int do_ifprefix(expr* e);

stmt_t* do_ifelse(stmt_t* ifstmt, stmt_t* elsestmt);

expr* do_idlist(char* name);

expr* do_moreID(char* name);

stmt_t* do_stmtlist(stmt_t* stmt_list, stmt_t* stmt);

void siuuuu_lib_funcs();

char* add_spaces(char* name, char* column);

void printArgs(expr* e, char* column);

void printQuads();

void convert_boolean(expr* e, int not);

void push_funclist(int label);

int pop_funclist();

void push_returnlist(int label);

int pop_returnlist();

#endif