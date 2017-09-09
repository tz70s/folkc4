/* 
* Tiny implementation of C interpreter, inspired by C4.
* Author @tz70s
*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "vm.h"

/* Some global variables */
int token; /* current token */
char *src, *old_src; /* pointer to source code string */
unsigned int line_number; /* line number */

/* next character */
void next() {
    /* skip whitespace */
    if (*src == ' ') {
        src++;
        return;
    }
    token = *src++;
}

/* parse the expression */
void parse_expr(int level) {
    /* do nothinh here */
}

void program() {
    /* get the next token */
    next();
    while (token > 0) {
        printf("token is: %c\n", token);
        next();
    }
}

int main(int argc, char **argv) {
    int fd, read_bytes;
    poolsize = 256 * 1024;
    line_number = 1;
    /* Initialized virtual machine */

    vm_init();   
    
    /* Read source file */
    if ((fd = open(argv[1], 0)) < 0) {
        printf("Could'nt open %s file \n", argv[1]);
        return -1;
    }
    
    if (!(src = old_src = (char*)malloc(poolsize))) {
        printf("Memory allocation failed\n");
        return -1;
    }

    if ((read_bytes = read(fd, src, poolsize-1)) <= 0) {
        printf("Read file failed\n");
        return -1;
    }
    
    /* add EOF character */ 
    src[read_bytes] = 0; 
    close(fd);

    program();
    return vm_run();
}
