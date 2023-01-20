%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../utils/util.h"
#include "tokens.h"

extern int pos;
int _pos=1;

int yywrap(void)
{
 _pos=1;
 return 1;
}

void adjust(void)
{
 pos=_pos;
 _pos+=yyleng;
}

%}

id [a-zA-Z][a-zA-Z0-9]*
num [0-9]+

%Start COMMENT
%%

<INITIAL>print {adjust(); return PRINT;}

<INITIAL>{id} {adjust(); yylval.sval = String(yytext); return ID;}
<INITIAL>{num} {adjust(); yylval.ival = atoi(yytext); return NUM;}

<INITIAL>"," {adjust(); return COMMA;}
<INITIAL>";" {adjust(); return SEMICOLON;}
<INITIAL>"(" {adjust(); return LPAREN;}
<INITIAL>")" {adjust(); return RPAREN;}
<INITIAL>"+" {adjust(); return PLUS;}
<INITIAL>"-" {adjust(); return MINUS;}
<INITIAL>"*" {adjust(); return TIMES;}
<INITIAL>"/" {adjust(); return DIV;}
<INITIAL>"=" {adjust(); return ASSIGN;}

<INITIAL>" "	 {adjust(); continue;}
<INITIAL>\n	 {adjust(); continue;}
<INITIAL>\t {adjust(); continue;}
<INITIAL>.	 {adjust(); fprintf(stderr, "illegal token");}

<INITIAL>"/*" {adjust(); BEGIN COMMENT;}
<COMMENT>"*/" {adjust(); BEGIN INITIAL;}
<COMMENT>. {adjust();}
