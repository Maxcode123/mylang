#include <criterion/criterion.h>

#include "../src/parser/grammar.h"

Test(testproductions, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
}