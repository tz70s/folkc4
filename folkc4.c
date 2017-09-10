/*
 * Tiny implementation of C interpreter, inspired by C4.
 * Author @tz70s
 */
#include "lexer.h"
#include "vm.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (!(src = old_src = (char *)malloc(poolsize))) {
        printf("Memory allocation failed\n");
        return -1;
    }

    if ((read_bytes = read(fd, src, poolsize - 1)) <= 0) {
        printf("Read file failed\n");
        return -1;
    }

    /* add EOF character */
    src[read_bytes] = 0;
    close(fd);

    program();
    return vm_run();
}
