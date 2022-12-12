#include <criterion/criterion.h>

#include "../src/parser/grammar.h"

Test(testitems, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    
    cr_assert(i->p->lhs == S_NT_PROGRAM);
    cr_assert(i->p->rhs[0] == S_NT_STM);
    cr_assert(i->p->rhs[1] == S_T_EOF);
    cr_assert(i->p->len == 2);
    cr_assert(i->before == 0);
}

Test(testitems, testarray)
{
    Production *prods = productions();
    LR0_Item *i = LR0_items(prods);
    cr_assert(i[0]->before == 0);
    cr_assert(i[0]->p->lhs == S_NT_PROGRAM);

    cr_assert(i[1]->before == -1);
    cr_assert(i[1]->p->lhs == S_NT_PROGRAM);

    cr_assert(i[2]->before == 0);
    cr_assert(i[2]->p->lhs == S_NT_STM);

    cr_assert(i[3]->before == 1);
    cr_assert(i[4]->before == 2);
    cr_assert(i[5]->before == -1);
}

Test(testitems, testeq)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i1 = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 0);
    cr_assert(LR0_itemeq(i1, i2));

    LR0_Item i3 = LR0_item(p, 2);
    cr_assert(!LR0_itemeq(i1, i3));

    Production p4 = production(S_NT_PROGRAM, rhs, 3);
    LR0_Item i4 = LR0_item(p4, 0);
    cr_assert(!LR0_itemeq(i1, i4));    
}

Test(testitems, testhash)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i1 = LR0_item(p, 0);

    symbol rhs2[] = {S_T_PRINT, S_T_LPAREN, S_NT_EXPLIST, S_T_RPAREN};
    Production p2 = production(S_NT_STM, rhs2, 4);
    LR0_Item i2 = LR0_item(p2, 0);
    LR0_Item i3 = LR0_item(p2, -1);
    
    char *hash = (char*)malloc(sizeof(char)*50);
    
    LR0_itemhash(i1, hash);
    cr_assert(strcmp(hash, "1011270") == 0);

    LR0_itemhash(i2, hash);
    cr_assert(strcmp(hash, "11232413250") == 0);

    LR0_itemhash(i3, hash);
    cr_assert(strcmp(hash, "1123241325-1") == 0);
}