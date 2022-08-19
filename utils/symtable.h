#ifndef SYMTABLE_H
#define SYMTABLE_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct symtable {
    struct SymbolTableEntry** table;
    unsigned int buckets;
    unsigned int size;
};

typedef enum SymbolType {
    GLOBAL,
    LOCAL,
    NO_LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
} Type;

typedef enum scopespace_t {
    programvar,
    functionlocal,
    formalarg
} scopespace_type;

typedef struct SymbolTableEntry {
    char* name;
    unsigned int scope;
    unsigned int line;
    unsigned int offset;
    unsigned int func_addr;
    unsigned int total_locals;
    unsigned int isActive;
    scopespace_type space;
    Type type;
    struct SymbolTableEntry* next;
    struct SymbolTableEntry* next_scope;
} SymbolTableEntry;

typedef struct FunctionOffset {
    int offset;
    struct FunctionOffset* next;
} FunctionOffset;

typedef struct LoopCounterStack {
    int loops;
    struct LoopCounterStack* next;
} LoopCounterStack;

typedef struct symtable* SymTable_T;

unsigned int SymTable_hash(const char *pcKey);

SymTable_T SymTable_new(void);

unsigned int SymTable_getLength(SymTable_T oSymTable);

int SymTable_insert(char* name, Type type);

int SymTable_hide(unsigned int scope);

int SymTable_lookup(char* name, Type type);

int in_scope(char* name, unsigned int scope);

int is_libfunc(char* name);

struct SymbolTableEntry* get_last_in_scope(struct SymbolTableEntry* scope);

struct SymbolTableEntry* SymTable_get_element_from_type(char* name, Type type);

struct SymbolTableEntry* SymTable_get_element_from_scope(char* name, int scope);

char* get_element_name(struct SymbolTableEntry* element);

enum scopespace_t currscopespace();

unsigned int currscope_offset();

void inc_currscope_offset();

void enter_scopespace();

void exit_scopespace();

void save_func_offset();

void new_func_offset(int offset);

void new_loop(int loop);

void exit_loop();

int pop_and_top();

#endif