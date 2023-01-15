#include "adapter.h"


YYSTYPE yylval;

int pos = 0;

int gettklen() {
    return tklen;
}

static void incrtklen() {
    tklen++;
}

Token *scan(char *fname) {
    yyset_in(fopen(fname, "r"));
    int i;
    Node h = lst_list();
    for (;;) {
        i = yylex();
        if (i == 0) break;
        incrtklen();
        lst_add(node("tk", token(i)), &h);
    }
    Token *t = malloc(sizeof(Token)*(lst_len(h)+1));
    t[lst_len(h)] = token(-1);
    incrtklen();
    int j = lst_len(h)-1;
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
        case -1: tk->s = S_T_EOF; break;
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