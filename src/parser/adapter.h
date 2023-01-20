#pragma once

#include "grammar.h"
#include "../scanner/tokens.h"

// Carries grammar symbol and semantic value
typedef struct _Token {
    symbol s;
    int pos;
    union {int ival; char* sval;};
} *Token;

// Length of token stream.
static int tklen;

// Increment scanned tokens coutner.
void incrtklen();

// Returns number of scanned tokens.
int gettklen();

// Sets the input stream
extern void yyset_in(FILE*);

// Prototype for the lexing function.
int yylex(void);

// Scans given file and creates token array.
Token *scan(char *fname);

// Creates token from given int.
Token token(int i);