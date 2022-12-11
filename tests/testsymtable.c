#include <criterion/criterion.h>

#include "../src/parser/symtable.h"

Test(testsymtable, testinit)
{
    SymTable st = symtable();
    cr_assert(st->head == NULL);
}

Test(testsymtable, testget)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);
    Item i2 = item(p, 2);

    ItemNode in = node("key1", i);
    ItemNode in2 = node("key2", i2);

    SymTable st = symtable();
    addin(in, &st->head);
    addin(in2, &st->head);

    Item _i, _i2;
 
    get(st, "key", &_i);
    cr_assert(_i == NULL);
    
    get(st, "key1", &_i);
    get(st, "key2", &_i2);
    cr_assert(itemeq(_i, i));
    cr_assert(itemeq(_i2, i2));
}