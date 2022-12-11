#pragma once

#include "util.h"

typedef union {
    int pos;
    int ival;
    string sval;
} YYSTYPE;
extern YYSTYPE yylval;

# define PLUS 257
# define MINUS 258
# define TIMES 259
# define DIV 260
# define ID 261
# define NUM 262
# define ASSIGN 263
# define LPAREN 264
# define RPAREN 265
# define COMMA 266
# define SEMICOLON 267
# define PRINT 268
