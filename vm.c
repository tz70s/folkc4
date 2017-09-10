/*
 * Tiny implementation of C interpreter, inspired by C4.
 * Author @tz70s
 */
#include "vm.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void vm_init() {
    /* allocate segments' memory */
    if (!(text_seg = dump_text = (int *)malloc(poolsize))) {
        printf("Memory allocation failed - text segment \n");
    }

    if (!(data = (char *)malloc(poolsize))) {
        printf("Memory allocation failed - data segment \n");
    }

    if (!(stack = (int *)malloc(poolsize))) {
        printf("Memory allocation failed - stack segment \n");
    }

    /* initialize memory */
    memset(text_seg, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);
}

int vm_run() {
    /* evaluate operations */
    return 0;
}
