/*
 * Tiny implementation of C interpreter, inspired by C4.
 * Author @tz70s
 */

#ifndef _VM_H_
#define _VM_H_

/* size of text/data/stack sections */
int poolsize;

/* segments */
int *text_seg, *dump_text, *stack;
char *data;

/* registers of vm */
int *pc, *bp, *sp, ax, cycle;

/* instructions and AT&T style */
enum {
    LEA,
    IMM, /* Put data into ax */
    JMP,
    CALL,
    JZ,
    JNZ,
    ENT,
    ADJ,
    LEV,
    LI, /* Put the address of integer into ax */
    LC, /* Put the address of char into ax */
    SI, /* Store the integer of ax into stack */
    SC, /* Store the character of ax into stack */
    PUSH,
    OR,
    XOR,
    AND,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    SHL,
    SHR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    /* c functions */
    OPEN,
    READ,
    CLOS,
    PRTF,
    MALC,
    MSET,
    MCMP,
    EXIT
};

void vm_init();
int vm_run();
#endif
