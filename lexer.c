/*
 * Tiny implementation of C interpreter, inspired by C4.
 * Author @tz70s
 */
#include "lexer.h"
#include "vm.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int num_val;

/* allocate memory of symbol table */
static int alloc_symtbl() {
    /* assign 1000 * identifier frame */
    if (!(symbol_table = (identifier *)malloc(sizeof(identifier) * 256))) {
        printf("cound'nt malloc memory for symbol table.\n");
        return -1;
    }
    memset(symbol_table, 0, sizeof(identifier) * 256);
    return 0;
}

/* next character */
static void next() {

    while ((token = *src) != 0) {
        ++src;
        if (token == '\n') {
            /* new line */
            ++line_number;

        } else if (token == '#') {
            /* skip macro until new line*/
            while (*src != 0 && *src != '\n') {
                ++src;
            }

        } else if ((token >= 'a' && token <= 'z') ||
                   (token >= 'A' && token <= 'Z') || (token == '_')) {
            /* is character */

            /* preserve for keep the whole identifer name */
            char *last_pos = src - 1;
            int hash = token;

            while ((*src >= 'a' && *src <= 'z') ||
                   (*src >= 'A' && *src <= 'Z') ||
                   (*src >= '0' && *src <= '9') || (*src == '_')) {
                hash = hash * 147 + *src;
                src++;
            }

            /* lookup symbol table */
            identifier *current_id = symbol_table;
            while (current_id->token) {
                if ((current_id->hash == hash) &&
                    !memcmp((char *)current_id->name, last_pos,
                            src - last_pos)) {
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
            num_val = token - '0';
            if (num_val > 0) {
                /* decimal */
                while (*src >= '0' && *src <= '9') {
                    /* translate the number from char to decimal */
                    num_val = num_val * 10 + *src++ - '0';
                }
            } else {
                token = *++src;
                if (token == 'x' || token == 'X') {
                    /* hex */
                    token = *++src;
                    while ((token >= '0' && token <= '9') ||
                           (token >= 'a' && token <= 'f') ||
                           (token >= 'A' && token <= 'F')) {
                        num_val = num_val * 16 + (token & 15) +
                                  (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else {
                    /* oct */
                    while (*src >= '0' && *src <= '7') {
                        num_val = num_val * 8 + *src++ - '0';
                    }
                }
            }

            token = Num;
            return;

        } else if (token == '"' || token == '\'') {
            /* parse string literal */
            /* store into the data segment */
            char *last_pos = data;
            while (*src != 0 && *src != token) {
                num_val = *src++;
                if (num_val == '\\') {
                    /* escape character */
                    num_val = *src++;
                    if (num_val == 'n') {
                        num_val = '\n';
                    }
                }
                if (token == '"') {
                    *data++ = num_val;
                }
            }

            src++;
            /* if it is a single character, return Num token */
            if (token == '"') {
                num_val = (int)last_pos;
            } else {
                token = Num;
            }

        } else if (token == '/') {
            /* comments */
            /* look ahead one LL(1) */
            if (*src == '/') {
                /* skip comments */
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
            } else {
                token = Div;
                return;
            }
        } else if (token == '=') {
            /* parse '==' and '=' */
            if (*src == '=') {
                src++;
                token = Eq;
            } else {
                token = Assign;
            }
            return;
        } else if (token == '+') {
            /* parse '+' and '++' */
            if (*src == '+') {
                src++;
                token = Inc;
            } else {
                token = Add;
            }
            return;
        } else if (token == '-') {
            /* parse '-' and '--' */
            if (*src == '-') {
                src++;
                token = Dec;
            } else {
                token = Sub;
            }
            return;

        } else if (token == '!') {
            /* '!=! */
            if (*src == '=') {
                src++;
                token = Ne;
            }
            return;
        } else if (token == '<') {
            /* parse '<=', '<<' or '<' */
            if (*src == '=') {
                src++;
                token = Le;
            } else if (*src == '<') {
                src++;
                token = Shl;
            } else {
                token = Lt;
            }
            return;

        } else if (token == '>') {
            // parse '>=', '>>' or '>'
            if (*src == '=') {
                src++;
                token = Ge;
            } else if (*src == '>') {
                src++;
                token = Shr;
            } else {
                token = Gt;
            }
            return;

        } else if (token == '|') {
            // parse '|' or '||'
            if (*src == '|') {
                src++;
                token = Lor;
            } else {
                token = Or;
            }
            return;

        } else if (token == '&') {
            // parse '&' and '&&'
            if (*src == '&') {
                src++;
                token = Lan;
            } else {
                token = And;
            }
            return;

        } else if (token == '^') {
            token = Xor;
            return;

        } else if (token == '%') {
            token = Mod;
            return;

        } else if (token == '*') {
            token = Mul;
            return;

        } else if (token == '[') {
            token = Brak;
            return;

        } else if (token == '?') {
            token = Cond;
            return;

        } else if (token == '~' || token == ';' || token == '{' ||
                   token == '}' || token == '(' || token == ')' ||
                   token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
            return;
        }
    }
}

/* parse the expression */
static void parse_expr(int level) { /* do nothinh here */
}

/* public function */
void program() {
    /* allocate symbol_table memory first */
    alloc_symtbl();
    /* get the next token */
    next();
    while (token > 0) {
        if (token == 128) {
            printf("(Num, %d), ", num_val);
        } else {
            printf("%d, ", token);
        }
        next();
    }
}
