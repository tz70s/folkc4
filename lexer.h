/* 
* Tiny implementation of C interpreter, inspired by C4.
* Author @tz70s
*/
#ifndef _LEXER_H_
#define _LEXER_H_

char *src, *old_src; /* pointer to source code string */
int token; /* current token */
unsigned int line_number; /* line number */

/* tokens and classes, operators are arranged in precedence order*/
enum {
    Num = 128, Fun, Sys, Glo, Loc, Id, Char, Else, Enum, If, Int, Return,
    Sizeof, While,Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, 
    Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

/* identifier frame */
typedef struct _identifier_ {
    int token;
    int hash;
    char *name;
    int scope_type;
    int type;
    int value;
    int b_class;
    int b_type;
    int b_value;
} identifier;

/* fields of identifiers */
enum {
    Token, Hash, Name, Type, Class, Value, B_Type, B_Class, B_Value, IdSize
};


identifier *symbol_table; /* symbol table */

/* start scanner */
void program();

#endif

