#pragma once
#include <stdlib.h>

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

typedef int symbol;

// Production rule
typedef struct _Production {
    symbol lhs; // left hand side symbol
    symbol *rhs; // rhs symbols
    int len; // length of rhs symbol array
} _Production;
typedef _Production *Production;

Production productions[14];
void init_productions();

// constructor
Production production(symbol lhs, symbol* rhs, int len);

// Item
typedef struct _Item {
    Production p;
    int before; // index of symbol that comes after dot, -1 if dot is last
} _Item;
typedef _Item *Item;

Item items[43];
void init_items();

// constructor
Item item(Production p, int before);
