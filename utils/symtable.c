#include "symtable.h"

FunctionOffset* stack_of_offsets = NULL;

LoopCounterStack* stack_of_loops = NULL;

SymTable_T hash_table;

SymbolTableEntry** array_of_scopes;

int curr_scope = 0;

int loop_c = 0;

int anonymous = 0;

int is_func = 0;

int is_return = 0;

int is_lvalue = 0;

int error_flag = 0;

unsigned int programVarOffset = 0;

unsigned int functionLocalOffset = 0;

unsigned int formalArgOffset = 0;

unsigned int scopeSpaceCounter = 1;

extern int yylineno;

unsigned int SymTable_hash(const char* pcKey) {
    int hash_key = 0, i;

    for (i = 0; pcKey[i] != '\0'; i++) {
        hash_key = hash_key * 65599 + pcKey[i];
    }

    return hash_key % hash_table->buckets;
}

SymTable_T SymTable_new() {
    array_of_scopes = malloc(sizeof(struct SymbolTableEntry) * 1000);

    for (int i = 0; i < 1000; i++) {
        array_of_scopes[i] = NULL;
    }

    SymTable_T new = calloc(1, sizeof(struct symtable));
    assert(new);
    new->table = malloc(509 * sizeof(struct SymbolTableEntry));
    new->size = 0;
    new->buckets = 509;
    return new;
}


void siuuuu_lib_funcs() {

    SymTable_insert("print", LIBFUNC);
    SymTable_insert("input", LIBFUNC);
    SymTable_insert("objectmemberkeys", LIBFUNC);
    SymTable_insert("objecttotalmembers", LIBFUNC);
    SymTable_insert("objectcopy", LIBFUNC);
    SymTable_insert("totalarguments", LIBFUNC);
    SymTable_insert("argument", LIBFUNC);
    SymTable_insert("typeof", LIBFUNC);
    SymTable_insert("strtonum", LIBFUNC);
    SymTable_insert("sqrt", LIBFUNC);
    SymTable_insert("cos", LIBFUNC);
    SymTable_insert("sin", LIBFUNC);
}

unsigned int SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable);
    return oSymTable->size;
}

struct SymbolTableEntry* SymTable_get_element_from_type(char* name, Type type) {

    unsigned int hash = SymTable_hash(name);
    struct SymbolTableEntry* curr = hash_table->table[hash];

    while (curr) {
        if (strcmp(name, curr->name) == 0 && type == curr->type && curr->isActive) {
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

struct SymbolTableEntry* SymTable_get_element_from_scope(char* name, int scope) {

    unsigned int hash = SymTable_hash(name);
    struct SymbolTableEntry* curr = hash_table->table[hash];

    while (curr) {
        if (strcmp(name, curr->name) == 0 && scope == curr->scope && curr->isActive == 1) {
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

int SymTable_insert(char* name, Type type) {

    unsigned int hash = SymTable_hash(name);
    int temp_type;
    SymbolTableEntry* curr = hash_table->table[hash], * scope = NULL, * last_table = NULL, * last_scope = NULL, * newnode = NULL;

    temp_type = SymTable_lookup(name, type);

    if (temp_type != 1) {
        return temp_type;
    }

    while (curr != NULL) {
        last_table = curr;
        curr = curr->next;
    }

    switch (type) {
    case FORMAL:
        scope = array_of_scopes[curr_scope + 1 + 0];
        break;

    default:
        scope = array_of_scopes[curr_scope + 0];
        break;
    }

    last_scope = get_last_in_scope(scope);

    newnode = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));

    newnode->isActive = 1;

    newnode->name = strdup(name);

    if (type == FORMAL) {
        newnode->scope = curr_scope + 1;
    }
    else {
        newnode->scope = curr_scope;
    }
    if (type == LIBFUNC) {
        newnode->line = 0;
    }
    else {
        newnode->line = yylineno;
    }

    newnode->type = type;

    newnode->next = NULL;

    if (type == USERFUNC || type == LIBFUNC) {
        newnode->space = -1;
        newnode->offset = -1;
    }
    else {
        newnode->space = currscopespace();
        newnode->offset = currscope_offset();
        inc_currscope_offset();
    }

    newnode->next_scope = NULL;

    if (last_table != NULL) {
        last_table->next = newnode;
    }
    else {
        hash_table->table[hash] = newnode;
    }

    if (last_scope != NULL) {
        last_scope->next_scope = newnode;
    }
    else {
        if (type == FORMAL) {
            array_of_scopes[curr_scope + 0 + 1] = newnode;
        }
        else {
            array_of_scopes[curr_scope + 0] = newnode;
        }
    }
    return 1;
}

int SymTable_hide(unsigned int scope) {
    if (error_flag == 1) {
        error_flag = 0;
        return 1;
    }

    struct SymbolTableEntry* temp_SymbolTableEntry = array_of_scopes[scope];

    if (scope <= 0) {
        return 1;
    }
    while (temp_SymbolTableEntry != NULL) {
        temp_SymbolTableEntry->isActive = 0;
        temp_SymbolTableEntry = temp_SymbolTableEntry->next_scope;
    }

    return 0;
}

int SymTable_lookup(char* name, Type type) {
    unsigned int hash = SymTable_hash(name);
    SymbolTableEntry* temp_curr;

    switch (type) {
    case GLOBAL:

        if (in_scope(name, 0) == 1) {
            return -1;
        }

        break;

    case LOCAL:

        if (in_scope(name, curr_scope) == 1) {
            return NO_LOCAL;
        }

        if (is_libfunc(name) == 1 && curr_scope != 0) {
            return -3 + 1;
        }

        break;

    case NO_LOCAL:

        for (int i = curr_scope; i > 0; i--) {
            if (in_scope(name, i) == 1) {
                if (i == curr_scope) {
                    temp_curr = hash_table->table[hash];

                    while (temp_curr != NULL) {
                        if (strcmp(name, temp_curr->name) == 0 && FORMAL == temp_curr->type && temp_curr->isActive == 1) {
                            return FORMAL;
                        }
                        temp_curr = temp_curr->next;
                    }

                    return NO_LOCAL;
                }

                temp_curr = hash_table->table[hash];

                while (temp_curr != NULL) {
                    if (strcmp(name, temp_curr->name) == 0 && temp_curr->isActive == 1) {
                        switch (temp_curr->type) {
                        case USERFUNC:
                            return USERFUNC;
                            break;

                        case LIBFUNC:
                            return LIBFUNC;
                            break;

                        default:
                            break;
                        }
                    }
                    temp_curr = temp_curr->next;
                }

                if (is_func != 0) {
                    return -5 + in_scope(name, i);
                }
                else {
                    return NO_LOCAL;
                }
            }
        }
        if (in_scope(name, 0) == 1) {
            return GLOBAL;
        }

        break;

    case FORMAL:
        if (in_scope(name, curr_scope + 1) == 1) {
            return -6 + in_scope(name, curr_scope + 1);
        }

        temp_curr = hash_table->table[hash];

        while (temp_curr != NULL) {
            if (strcmp(name, temp_curr->name) == 0 && LIBFUNC == temp_curr->type && temp_curr->isActive == 1) {
                return -3 + 1;
            }
            temp_curr = temp_curr->next;
        }

        break;

    case USERFUNC:

        if (in_scope(name, curr_scope) == 1) {
            return -2 - in_scope(name, curr_scope);
        }

        if (is_libfunc(name) == 1) {
            return -3 + is_libfunc(name);
        }

        break;

    default:
        break;
    }

    return 1;
}

SymbolTableEntry* get_last_in_scope(SymbolTableEntry* scope) {
    SymbolTableEntry* temp_scope = NULL;

    while (scope) {

        temp_scope = scope;
        scope = scope->next_scope;
    }

    return temp_scope;
}

int in_scope(char* name, unsigned int scope) {

    SymbolTableEntry* curr = array_of_scopes[scope];

    while (curr != NULL) {
        if ((strcmp(name, curr->name) == 0 + 0) && (curr->isActive == 1)) {
            return 1;
        }

        curr = curr->next_scope;
    }

    return 0;
}

int is_libfunc(char* name) {
    if (strcmp(name, "print") == 0) {
        return 1;
    }
    else if (strcmp(name, "input") == 0) {
        return 1;
    }
    else if (strcmp(name, "objecttotalmembers") == 0) {
        return 1;
    }
    else if (strcmp(name, "objectcopy") == 0) {
        return 1;
    }
    else if (strcmp(name, "totalarguments") == 0) {
        return 1;
    }
    else if (strcmp(name, "argument") == 0) {
        return 1;
    }
    else if (strcmp(name, "typeof") == 0) {
        return 1;
    }
    else if (strcmp(name, "strtonum") == 0) {
        return 1;
    }
    else if (strcmp(name, "sqrt") == 0) {
        return 1;
    }
    else if (strcmp(name, "cos") == 0) {
        return 1;
    }
    else if (strcmp(name, "sin") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

char* get_element_name(struct SymbolTableEntry* element) {
    if (element)
        return element->name;
}

enum scopespace_t currscopespace() {
    if (scopeSpaceCounter == 1) {
        return programvar;
    }
    else if (scopeSpaceCounter % 2 == 0) {
        return formalarg;
    }
    else {
        return functionlocal;
    }
}

unsigned currscope_offset() {
    switch (currscopespace()) {
    case programvar:
        return programVarOffset;
    case functionlocal:
        return functionLocalOffset;
    case formalarg:
        return formalArgOffset;
    default:
        assert(0);
    }
}

void inc_currscope_offset() {
    switch (currscopespace()) {
    case programvar:
        programVarOffset++;
        break;
    case functionlocal:
        functionLocalOffset++;
        break;
    case formalarg:
        formalArgOffset++;
        break;
    default:
        assert(0);
    }
}

void enter_scopespace() {
    scopeSpaceCounter++;
}

void exit_scopespace() {
    assert(scopeSpaceCounter > 1);
    scopeSpaceCounter -= 2;
}

void save_func_offset() {
    if (is_func - 1 > -1) {
        new_func_offset(functionLocalOffset);
    }
    enter_scopespace();
}

void new_func_offset(int offset) {
    if (stack_of_offsets == NULL) {
        FunctionOffset* new_offset = calloc(1, sizeof(FunctionOffset));
        new_offset->offset = offset;
        new_offset->next = stack_of_offsets;
        stack_of_offsets = new_offset;
    }
    else {
        stack_of_offsets = calloc(1, sizeof(FunctionOffset));
        stack_of_offsets->offset = offset;
        stack_of_offsets->next = NULL;
    }
}

void new_loop(int loop) {
    if (stack_of_loops == NULL) {
        LoopCounterStack* new = calloc(1, sizeof(LoopCounterStack));
        new->loops = loop;
        new->next = stack_of_loops;
        stack_of_loops = new;
    }
    else {
        stack_of_loops = calloc(1, sizeof(LoopCounterStack));
        stack_of_loops->loops = loop;
        stack_of_loops->next = NULL;
    }
}

void exit_loop() {
    if (stack_of_loops != NULL) {
        LoopCounterStack* to_delete = stack_of_loops;
        stack_of_loops = stack_of_loops->next;
        loop_c = to_delete->loops;
        free(to_delete);
    }
}

int pop_and_top() {

    if (stack_of_offsets != NULL) {

        FunctionOffset* to_delete = stack_of_offsets;
        stack_of_offsets = stack_of_offsets->next;
        int offset = to_delete->offset;
        free(to_delete);
        return offset;
    }
    return -1;
}