#include "grammar.h"

Production production(symbol lhs, symbol* rhs, int len) {
    Production p = malloc(sizeof(_Production));
    p->lhs = lhs;
    p->rhs = rhs;
    p->len = len;
    return p;
}

void init_productions() {
    symbol p1[] = {S_NT_STM, S_T_EOF};
    symbol p2[] = {S_NT_STM, S_T_SEMICOLON, S_NT_STM};
    symbol p3[] = {S_T_ID, S_T_EQ, S_NT_EXP};
    symbol p4[] = {S_T_PRINT, S_T_LPAREN, S_NT_EXPLIST, S_T_RPAREN};
    symbol p5[] = {S_T_ID};
    symbol p6[] = {S_T_NUM};
    symbol p7[] = {S_NT_EXP, S_NT_BINOP, S_NT_EXP};
    symbol p8[] = {S_T_LPAREN, S_NT_STM, S_T_COMMA, S_NT_EXP, S_T_RPAREN};
    symbol p9[] = {S_NT_EXP, S_T_COMMA, S_NT_EXPLIST};
    symbol p10[] = {S_NT_EXP};
    symbol p11[] = {S_T_PLUS};
    symbol p12[] = {S_T_MINUS};
    symbol p13[] = {S_T_TIMES};
    symbol p14[] = {S_T_DIV};
    

    productions[0] = production(S_NT_PROGRAM, p1, 2);
    productions[1] = production(S_NT_STM, p2, 3);
    productions[2] = production(S_NT_STM, p3, 3);
    productions[3] = production(S_NT_STM, p4, 4);
    productions[4] = production(S_NT_EXP, p5, 1);
    productions[5] = production(S_NT_EXP, p6, 1);
    productions[6] = production(S_NT_EXP, p7, 3);
    productions[7] = production(S_NT_EXP, p8, 5);
    productions[8] = production(S_NT_EXPLIST, p9, 3);
    productions[9] = production(S_NT_EXPLIST, p10, 1);
    productions[10] = production(S_NT_BINOP, p11, 1);
    productions[11] = production(S_NT_BINOP, p12, 1);
    productions[12] = production(S_NT_BINOP, p13, 1);
    productions[13] = production(S_NT_BINOP, p14, 1);

}

Item item(Production p, int before) {
    Item i = malloc(sizeof(_Item));
    i->p = p;
    i->before = before;
    return i;
}