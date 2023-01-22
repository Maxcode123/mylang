#include <criterion/criterion.h>

#include "../src/parser/parser.h"
#include "../src/semantics/env.h"

Test(testchecker, testchecker)
{
    // a = a
    Token *ta = malloc(sizeof(Token)*4);
    ta[0] = (yylval.sval = String("a"), incrtklen(), token(ID));
    ta[1] = (incrtklen(), token(ASSIGN));
    ta[2] = (yylval.sval = String("a"), incrtklen(), token(ID));
    ta[3] = (incrtklen(), token(-1));
    parse(ta);
    checkuses();
}
