#include <criterion/criterion.h>

#include "../src/utils/symtable.h"
#include "../src/parser/grammar.h"

Test(testsymtable, testinit)
{
    SymTable st = stb_symtable();
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
    SymTable st = stb_symtable();
    lst_add(in, (Node*)&st->head);
    lst_add(in2, (Node*)&st->head);

    LR0_Item _i, _i2;

    stb_get(st, "key", &_i);
    cr_assert(_i == NULL);

    stb_get(st, "key1", &_i);
    stb_get(st, "key2", &_i2);
    cr_assert(LR0_itemeq(_i, i));
    cr_assert(LR0_itemeq(_i2, i2));
}

Test(testsymtable, testhaskey)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

    SymTable st = stb_symtable();
    lst_add(in, (Node*)&st->head);
    lst_add(in2, (Node*)&st->head);

    LR0_Item _i, _i2;

    cr_assert(!stb_haskey(st, "key"));
    cr_assert(stb_haskey(st, "key1"));
    cr_assert(stb_haskey(st, "key2"));
}

Test(testsymtable, testput)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

    SymTable st = stb_symtable();

    stb_put(st, in);
    stb_put(st, in2);
    stb_put(st, in2);

    cr_assert(LR0_itemeq(lst_get(in->k, st->head)->i, i));
    cr_assert(LR0_itemeq(lst_get(in2->k, st->head)->i, i2));
}

Test(testsymtable, testlen)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);

    SymTable st = stb_symtable();

    cr_assert(stb_len(st) == 0);

    stb_put(st, in);
    stb_put(st, in2);

    cr_assert(stb_len(st) == 2);
}

Test(testsymtable, testnode)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    Node in = stb_node(i, &LR0_itemhash);
    cr_assert(strcmp(in->k, "1011270") == 0);
}

Test(testsymtable, testunion)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 1);
    LR0_Item i3 = LR0_item(p, -1);

    Node in = stb_node(i, &LR0_itemhash);
    Node in2 = stb_node(i2, &LR0_itemhash);
    Node in3 = stb_node(i3, &LR0_itemhash);
    Node in4 = stb_node(i3, &LR0_itemhash); // same as node in3

    SymTable st1 = stb_symtable();
    SymTable st2 = stb_symtable();

    stb_put(st1, in);
    stb_put(st1, in3);

    stb_put(st2, in2);
    stb_put(st2, in4);

    stb_union(st1, st2, &LR0_itemhash, st1->head, &LR0_itemeq);

    cr_assert(nodeeq(st1->head, in2, &LR0_itemeq));
    cr_assert(nodeeq(st1->head->next, in3, &LR0_itemeq));
    cr_assert(nodeeq(st1->head->next->next, in, &LR0_itemeq));
    cr_assert(st1->head->next->next->next == NULL);

    // should not affect set st1
    stb_union(st1, st2, &LR0_itemhash, st1->head->next, &LR0_itemeq);
    cr_assert(nodeeq(st1->head, in2, &LR0_itemeq));
    cr_assert(nodeeq(st1->head->next, in3, &LR0_itemeq));
    cr_assert(nodeeq(st1->head->next->next, in, &LR0_itemeq));
    cr_assert(st1->head->next->next->next == NULL);
}