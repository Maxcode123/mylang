#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include "../utils/util.h"
#include "../utils/list.h"


// Non terminal symbols
#define S_NT_PROGRAM 10 // program should always be first non terminal symbol
#define S_NT_STM 11
#define S_NT_EXP 12
#define S_NT_EXPLIST 13
#define S_NT_BINOP 14

// Terminal symbols
#define S_T_ID 15
#define S_T_NUM 16
#define S_T_COMMA 17
#define S_T_SEMICOLON 18
#define S_T_PLUS 19
#define S_T_MINUS 20
#define S_T_TIMES 21
#define S_T_DIV 22
#define S_T_PRINT 23
#define S_T_LPAREN 24
#define S_T_RPAREN 25
#define S_T_EQ 26
#define S_T_EOF 27

#define NON_TERMINALS 5 // number of non terminal symbols
#define SYMBOLS 18 // number of symbols
#define PRODUCTIONS 14 // number of productions
#define ITEMS 43 // number of items

#define IS_TERMINAL(x) (x >= S_NT_PROGRAM + NON_TERMINALS)
#define IS_SEMANTIC(x) (x == S_T_NUM || x == S_T_ID || x == S_T_PLUS || x == S_T_MINUS || x == S_T_TIMES || x == S_T_DIV)

#define PRODUCTION_NOT_FOUND -1

static char *symbols[] = {
    "program",
    "Stm",
    "Exp",
    "ExpList",
    "BinOp",
    "id",
    "num",
    ",",
    ";",
    "+",
    "-",
    "*",
    "/",
    "print",
    "(",
    ")",
    "=",
    "$"
};

typedef int symbol;
typedef Node ItemNode;

// Returns symbols string array
char **getsymbols();

// Production rule
typedef struct _Production {
    symbol lhs; // left hand side symbol
    symbol *rhs; // rhs symbols
    int len; // length of rhs symbol array
} *Production;

// Production rhs constructor, allocates memory for rhs symbol array.
symbol *sarr(int count, ...);

// Production constructor, allocates memory for Production.
Production production(symbol lhs, symbol* rhs, int len);

// Equality comparison between two Productions.
bool prodeq(Production p1, Production p2);

/* Allocates memory for array of productions, creates and inserts productions,
returns pointer. */
Production *productions();

// Static array of all productions.
static Production *prods;

// Initializes all productions.
void initprods();

// Returns array of all productions.
Production *getprods();

/* Returns the index of the given production in the productions array. Returns
PRODUCTION_NOT_FOUND if production is not found. */
int prodidx(Production p);

// Prints production in nice format.
void printprod(Production p);

// Item
typedef struct _LR0_Item {
    Production p;
    int before; // index of symbol that comes after dot, -1 if dot is last
} *LR0_Item;

// Item constructor
LR0_Item LR0_item(Production p, int before);

// Equality comparison between two Items.
bool LR0_itemeq(LR0_Item i1, LR0_Item i2);

// Insert hash of item i into given hash.
void LR0_itemhash(LR0_Item i, key hash);

/* Allocates memory for array of items, creates and inserts items, returns 
pointer. */
LR0_Item *LR0_items(Production *prods);

// static array of all items
static LR0_Item *LR0_allitems;

// Initializes static array of all items.
void LR0_inititems();

// Returns array of all items.
LR0_Item *LR0_getallitems();

// Returns the index of item i in the array of all items.
int LR0_getindex(LR0_Item i);

// Print item in nice format.
void printit(LR0_Item i);