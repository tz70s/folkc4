/* 
* Tiny implementation of C interpreter, inspired by C4.
* Author @tz70s
*/
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "lexer.h"
#include "vm.h"

/* allocate memory of symbol table */
static int alloc_symtbl() {
    /* assign 1000 * identifier frame */
    if (!(symbol_table = (identifier *)malloc(sizeof(identifier)*1000))) {
        printf("cound'nt malloc memory for symbol table.\n");
        return -1;
    }
    memset(symbol_table, 0, sizeof(identifier)*1000);
    return 0;
}

/* next character */
static void next() {
    
    while (token = *src) {
        ++src;
        
        if (token == '\n') {
            /* new line */
            ++line_number;
        } else if (token == '#') {
           /* skip macro until new line*/
           while (*src != 0 && *src != '\n') {
              ++src;
           }
        } else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {
            /* is character */

            /* preserve for keep the whole identifer name */
            char *last_pos = src - 1;
            int hash = token;
            
            while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {
                hash = hash * 147 + *src;
                src++;    
            }
            
            /* lookup symbol table */
            identifier *current_id = symbol_table;
            while (current_id->token) {
                if (current_id->hash == hash && !memcmp((char *)current_id->name, last_pos, src - last_pos)) {
                    /* found the same token */
                    token = current_id->token;
                    return;
                }
                /* linear lookup, move to the next frame */
                ++current_id;
            }

            /* store new id */
            current_id->name = last_pos;
            current_id->hash = hash;
            token = current_id->token = Id;
            return;

        } else if ((token >= '0' && token <= '9')) {
            /* parse number, three types: dec(123), hex(0x123), oct(0123) */
            int token_val = token - '0';
            if (token_val > 0) {
                /* decimal */
                while (*src >= '0' && *src <= '9') {
                    /* translate the number from char to decimal */
                    token_val = token_val*10 + *src++ - '0';
                }
            } else {
                token = *++src;
                if (token == 'x' || token == 'X') {
                    /* hex */
                    token = *++src;
                    while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
                        token_val = token_val*16 + (token & 15) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    /* oct */
                    while (*src >= '0' && *src <= '7') {
                        token_val = token_val*8 + *src++ - '0';
                    }
                }
            }
            
            token = Num;

            return;
        }
    }
}

/* parse the expression */
static void parse_expr(int level) {
    /* do nothinh here */
}

/* public function */
void program() {
    /* allocate symbol_table memory first */
    alloc_symtbl();

    /* get the next token */
    next();
    while (token > 0) {
        printf("token is: %c\n", token);
        next();
    }
}

