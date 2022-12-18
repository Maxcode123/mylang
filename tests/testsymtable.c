#include <criterion/criterion.h>

#include "../src/utils/symtable.h"
#include "../src/parser/grammar.h"

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

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

    SymTable st = ST_symtable();
    add(in, (Node*)&st->head);
    add(in2, (Node*)&st->head);

    LR0_Item _i, _i2;

    ST_haskey(st, "key", &_i);
    cr_assert(_i == NULL);

    ST_haskey(st, "key1", &_i);
    ST_haskey(st, "key2", &_i2);
    cr_assert(LR0_itemeq(_i, i));
    cr_assert(LR0_itemeq(_i2, i2));
}

Test(testsymtable, testput)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

    SymTable st = ST_symtable();

    ST_put(st, in);
    ST_put(st, in2);
    ST_put(st, in2);

    cr_assert(LR0_itemeq(get(in->k, st->head)->i, i));
    cr_assert(LR0_itemeq(get(in2->k, st->head)->i, i2));
}

Test(testsymtable, testlen)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

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

    Node in = ST_node(i, &LR0_itemhash);
    cr_assert(strcmp(in->k, "1011270") == 0);
}

Test(testsymtable, testunion)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 1);
    LR0_Item i3 = LR0_item(p, -1);

    Node in = ST_node(i, &LR0_itemhash);
    Node in2 = ST_node(i2, &LR0_itemhash);
    Node in3 = ST_node(i3, &LR0_itemhash);
    Node in4 = ST_node(i3, &LR0_itemhash);

    SymTable st1 = ST_symtable();
    SymTable st2 = ST_symtable();

    ST_put(st1, in);
    ST_put(st1, in3);

    ST_put(st2, in2);
    ST_put(st2, in4);

    ST_union(st1, st2, &LR0_itemhash);

    cr_assert(nodeeq(st1->head, in3, &LR0_itemeq));
    cr_assert(nodeeq(((Node)st1->head)->next, in2, &LR0_itemeq));
    cr_assert(nodeeq(((Node)st1->head)->next->next, in, &LR0_itemeq));
    cr_assert(((Node)st1->head)->next->next->next == NULL);
}