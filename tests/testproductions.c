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
    cr_assert(p[1]->rhs[0] == S_NT_STM);
    cr_assert(p[2]->len == 3);
}