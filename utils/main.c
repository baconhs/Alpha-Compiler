#include "vm.h"

extern unsigned totGlobals, top, topsp, executionFinished;

int main(void) {
    read_bin_file();
    avm_initstack();
    top = AVM_STACKSIZE - totGlobals - 2;
    topsp = AVM_STACKSIZE - totGlobals - 2;

    while (!executionFinished) {
        execute_cycle();
    }

    return 0;
}