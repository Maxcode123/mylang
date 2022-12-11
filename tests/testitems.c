#include <criterion/criterion.h>

#include "../src/parser/grammar.h"

Test(testitems, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);
    
    cr_assert(i->p->lhs == S_NT_PROGRAM);
    cr_assert(i->p->rhs[0] == S_NT_STM);
    cr_assert(i->p->rhs[1] == S_T_EOF);
    cr_assert(i->p->len == 2);
    cr_assert(i->before == 0);
}

Test(testitems, testarray)
{
    Production *prods = productions();
    Item *i = items(prods);
    cr_assert(i[0]->before == 0);
    cr_assert(i[1]->before == -1);
    cr_assert(i[2]->before == 0);
    cr_assert(i[3]->before == 1);
    cr_assert(i[4]->before == 2);
    cr_assert(i[5]->before == -1);
}

Test(testitems, testeq)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i1 = item(p, 0);
    Item i2 = item(p, 0);
    cr_assert(itemeq(i1, i2));

    Item i3 = item(p, 2);
    cr_assert(!itemeq(i1, i3));

    Production p4 = production(S_NT_PROGRAM, rhs, 3);
    Item i4 = item(p4, 0);
    cr_assert(!itemeq(i1, i4));    
}
