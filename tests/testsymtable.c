#include <criterion/criterion.h>

#include "../src/parser/symtable.h"

Test(testsymtable, testinit)
{
    LR0_SymTable st = LR0_symtable();
    cr_assert(st->head == NULL);
}

Test(testsymtable, testget)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i2);

    LR0_SymTable st = LR0_symtable();
    LR0_add(in, &st->head);
    LR0_add(in2, &st->head);

    LR0_Item _i, _i2;

    LR0_ST_get(st, "key", &_i);
    cr_assert(_i == NULL);

    LR0_ST_get(st, "key1", &_i);
    LR0_ST_get(st, "key2", &_i2);
    cr_assert(LR0_itemeq(_i, i));
    cr_assert(LR0_itemeq(_i2, i2));
}

Test(testsymtable, testput)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i2);

    LR0_SymTable st = LR0_symtable();

    LR0_ST_put(st, in);
    LR0_ST_put(st, in2);
    LR0_ST_put(st, in2);

    cr_assert(LR0_itemeq(LR0_get(in->k, st->head)->i, i));
    cr_assert(LR0_itemeq(LR0_get(in2->k, st->head)->i, i2));
}

Test(testsymtable, testlen)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i2);

    LR0_SymTable st = LR0_symtable();

    cr_assert(LR0_ST_len(st) == 0);

    LR0_ST_put(st, in);
    LR0_ST_put(st, in2);

    cr_assert(LR0_ST_len(st) == 2);
}

Test(testsymtable, testnode)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    LR0_ItemNode in = LR0_ST_node(i);
    cr_assert(strcmp(in->k, "1011270") == 0);
}
