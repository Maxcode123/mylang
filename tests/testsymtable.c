#include <criterion/criterion.h>

#include "../src/parser/symtable.h"

Test(testsymtable, testinit)
{
    SymTable st = ST_symtable();
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

    SymTable st = ST_symtable();
    LR0_add(in, (LR0_ItemNode*)&st->head);
    LR0_add(in2, (LR0_ItemNode*)&st->head);

    LR0_Item _i, _i2;

    ST_get(st, "key", &_i);
    cr_assert(_i == NULL);

    ST_get(st, "key1", &_i);
    ST_get(st, "key2", &_i2);
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

    SymTable st = ST_symtable();

    ST_put(st, in);
    ST_put(st, in2);
    ST_put(st, in2);

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

    SymTable st = ST_symtable();

    cr_assert(ST_len(st) == 0);

    ST_put(st, in);
    ST_put(st, in2);

    cr_assert(ST_len(st) == 2);
}

Test(testsymtable, testnode)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    LR0_ItemNode in = ST_node(i);
    cr_assert(strcmp(in->k, "1011270") == 0);
}

Test(testsymtable, testunion)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 1);
    LR0_Item i3 = LR0_item(p, -1);

    LR0_ItemNode in = ST_node(i);
    LR0_ItemNode in2 = ST_node(i2);
    LR0_ItemNode in3 = ST_node(i3);
    LR0_ItemNode in4 = ST_node(i3);

    SymTable st1 = ST_symtable();
    SymTable st2 = ST_symtable();

    ST_put(st1, in);
    ST_put(st1, in3);

    ST_put(st2, in2);
    ST_put(st2, in4);

    ST_union(st1, st2);

    cr_assert(LR0_ninodeeq(st1->head, in3));
    cr_assert(LR0_ninodeeq(((LR0_ItemNode)st1->head)->next, in2));
    cr_assert(LR0_ninodeeq(((LR0_ItemNode)st1->head)->next->next, in));
    cr_assert(((LR0_ItemNode)st1->head)->next->next->next == NULL);
}