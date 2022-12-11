#include <criterion/criterion.h>

#include "../src/parser/grammar.h"

Test(testproductions, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    
    cr_assert(p->lhs == S_NT_PROGRAM);
    cr_assert(p->rhs[0] == S_NT_STM);
    cr_assert(p->rhs[1] == S_T_EOF);
    cr_assert(p->len == 2);
}

Test(testproductions, testarray)
{
    Production *p = productions();
    cr_assert(p[0]->lhs == S_NT_PROGRAM);
    cr_assert(p[0]->len == 1);
    cr_assert(p[1]->rhs[0] == S_NT_STM);
    cr_assert(p[2]->len == 3);
    cr_assert(p[PRODUCTIONS-1]->lhs == S_NT_BINOP);
}

Test(testproductions, testeq)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p1 = production(S_NT_PROGRAM, rhs, 2);
    Production p2 = production(S_NT_PROGRAM, rhs, 2);
    cr_assert(prodeq(p1, p2));

    Production p3 = production(S_NT_BINOP, rhs, 2);
    cr_assert(!prodeq(p1, p3));

    symbol rhs4[] = {S_NT_EXP, S_NT_BINOP, S_NT_EXP};
    Production p4 = production(S_NT_PROGRAM, rhs4, 2);
    cr_assert(!prodeq(p1, p4));

    Production p5 = production(S_NT_PROGRAM, rhs, 3);
    cr_assert(!prodeq(p1, p5));
}