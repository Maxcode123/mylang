#include "adapter.h"


YYSTYPE yylval;

int pos = 0;


Token *scan(char *fname) {
    yyset_in(fopen(fname, "r"));
    int i;
    Node h = list();
    for (;;) {
        i = yylex();
        if (i == 0) break;
        add(node("tk", token(i)), &h);
    }
    Token *t = malloc(sizeof(Token)*len(h));
    int j = len(h)-1;
    Node n = h;
    while (n != NULL) {
        t[j--] = (Token)n->i;
        n = n->next;
    }
    return t;
}

Token token(int i) {
    Token tk = malloc(sizeof(struct _Token));
    tk->pos = pos;
    switch (i) {
        case PLUS: tk->s = S_T_PLUS; break;
        case MINUS: tk->s = S_T_MINUS; break;
        case TIMES: tk->s = S_T_TIMES; break;
        case DIV: tk->s = S_T_DIV; break;
        case ID: tk->s = S_T_ID; tk->sval = yylval.sval; break;
        case NUM: tk->s = S_T_NUM; tk->ival = yylval.ival; break;
        case ASSIGN: tk->s = S_T_EQ; break;
        case LPAREN: tk->s = S_T_LPAREN; break;
        case RPAREN: tk->s = S_T_RPAREN; break;
        case COMMA: tk->s = S_T_COMMA; break;
        case SEMICOLON: tk->s = S_T_SEMICOLON; break;
        case PRINT: tk->s = S_T_PRINT; break;
    }
}