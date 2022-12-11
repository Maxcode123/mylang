#include "grammar.h"

Production production(symbol lhs, symbol* rhs, int len) {
    Production p = malloc(sizeof(struct _Production));
    p->lhs = lhs;
    p->rhs = rhs;
    p->len = len;
    return p;
}

bool prodeq(Production p1, Production p2) {
    if (p1->lhs != p2->lhs) return false;
    if (p1->len != p2->len) return false;
    for (int i = 0; i < p1->len; i++) {
        if (p1->rhs[i] != p2->rhs[i]) return false;
    }
    return true;
}

Production *productions() {
    symbol p1[] = {S_NT_STM};
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

    Production *p = malloc(PRODUCTIONS*sizeof(Production));
    
    p[0] = production(S_NT_PROGRAM, p1, 1);
    p[1] = production(S_NT_STM, p2, 3);
    p[2] = production(S_NT_STM, p3, 3);
    p[3] = production(S_NT_STM, p4, 4);
    p[4] = production(S_NT_EXP, p5, 1);
    p[5] = production(S_NT_EXP, p6, 1);
    p[6] = production(S_NT_EXP, p7, 3);
    p[7] = production(S_NT_EXP, p8, 5);
    p[8] = production(S_NT_EXPLIST, p9, 3);
    p[9] = production(S_NT_EXPLIST, p10, 1);
    p[10] = production(S_NT_BINOP, p11, 1);
    p[11] = production(S_NT_BINOP, p12, 1);
    p[12] = production(S_NT_BINOP, p13, 1);
    p[13] = production(S_NT_BINOP, p14, 1);

    return p;
}

Item item(Production p, int before) {
    if (before < -1 || before > p->len) {
        fprintf(stderr, "Cannot initialize Item. Invalid 'before' index.");
        exit(1);
    }
    Item i = malloc(sizeof(struct _Item));
    i->p = p;
    i->before = before;
    return i;
}

bool itemeq(Item i1, Item i2) {
    return (prodeq(i1->p, i2->p) & i1->before == i2->before);
}

Item *items(Production *prods) {

    Item *i = malloc(ITEMS*sizeof(Item));
    int c = 0;
    for (int j = 0; j < PRODUCTIONS; j++) {
        for (int k = 0; k < prods[j]->len; k++) {
            Item tmp = item(prods[j], k);
            i[c++] = tmp;
        }
        Item _tmp = item(prods[j], -1); // last item, where dot is after last symbol
        i[c++] = _tmp;
    }
    return i;
}