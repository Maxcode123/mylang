#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Non terminal symbols
# define S_NT_PROGRAM 10
# define S_NT_STM 11
# define S_NT_EXP 12
# define S_NT_EXPLIST 13
# define S_NT_BINOP 14

// Terminal symbols
# define S_T_ID 15
# define S_T_NUM 16
# define S_T_COMMA 17
# define S_T_SEMICOLON 18
# define S_T_PLUS 19
# define S_T_MINUS 20
# define S_T_TIMES 21
# define S_T_DIV 22
# define S_T_PRINT 23
# define S_T_LPAREN 24
# define S_T_RPAREN 25
# define S_T_EQ 26
# define S_T_EOF 27

# define PRODUCTIONS 14
# define ITEMS 43

typedef int symbol;

// Production rule
typedef struct _Production {
    symbol lhs; // left hand side symbol
    symbol *rhs; // rhs symbols
    int len; // length of rhs symbol array
} *Production;

// Production constructor
Production production(symbol lhs, symbol* rhs, int len);

// Equality comparison between two Productions.
bool prodeq(Production p1, Production p2);

/* Allocates memory for array of productions, creates and inserts productions,
returns pointer. */
Production *productions();

// Item
typedef struct _LR0_Item {
    Production p;
    int before; // index of symbol that comes after dot, -1 if dot is last
} *LR0_Item;

// Item constructor
LR0_Item LR0_item(Production p, int before);

// Equality comparison between two Items.
bool LR0_itemeq(LR0_Item i1, LR0_Item i2);

// Insert hash of item into given pointer.
void LR0_itemhash(LR0_Item i, char *hash);

/* Allocates memory for array of items, creates and inserts items, returns 
pointer. */
LR0_Item *LR0_items(Production *prods);
