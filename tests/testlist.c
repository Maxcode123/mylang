#include <criterion/criterion.h>

#include "../src/parser/list.h"

Test(testlist, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    LR0_ItemNode in = LR0_node("key1", i);
    cr_assert(strcmp(in->k, "key1") == 0);
    cr_assert(LR0_itemeq(in->i, i));
    cr_assert(in->next == NULL);
}

Test(testlist, testinodeeq)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key1", i);
    LR0_ItemNode in3 = LR0_node("key2", i);
    LR0_ItemNode in4 = LR0_node("key1", i2);

    cr_assert(LR0_inodeeq(in, in2));
    cr_assert(!LR0_inodeeq(in, in3));
    cr_assert(!LR0_inodeeq(in, in4));
}

Test(testlist, testlistinit)
{
    LR0_ItemNode in = LR0_list();
    cr_assert(in == NULL);
}

Test(testlist, testadd)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    LR0_ItemNode in = LR0_node("key1", i);

    LR0_ItemNode h = LR0_list();
    LR0_add(in, &h);
    cr_assert(strcmp(h->k, "key1") == 0);
    cr_assert(LR0_itemeq(h->i, i));
    cr_assert(h->next == NULL);

    LR0_ItemNode in2 = LR0_node("key2", i);
    LR0_add(in2, &h);
    cr_assert(strcmp(h->k, "key2") == 0);
    cr_assert(LR0_itemeq(h->i, i));
    cr_assert(h->next == in);
}

Test(testlist, testget)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i);
    LR0_ItemNode in3 = LR0_node("key3", i2);
    LR0_ItemNode h = LR0_list();
    LR0_add(in, &h);
    LR0_add(in2, &h);
    LR0_add(in3, &h);

    LR0_ItemNode _in = LR0_get("key1", h);
    cr_assert(LR0_inodeeq(_in, in));

    LR0_ItemNode _in2 = LR0_get("key2", h);
    cr_assert(LR0_inodeeq(_in2, in2));

    LR0_ItemNode _in3 = LR0_get("key3", h);
    cr_assert(LR0_inodeeq(_in3, in3));

    LR0_ItemNode _in4 = LR0_get("asdas", h);
    cr_assert(_in4 == NULL);
}

Test(testlist, testsubs)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode h = LR0_list();
    LR0_add(in, &h);

    LR0_subs("key1", i2, h);
    LR0_ItemNode _in = LR0_get("key1", h);
    cr_assert(LR0_itemeq(_in->i, i2));

    free(LR0_get("key1", h)->i);
    LR0_subs("key1", i, h);
    _in = LR0_get("key1", h);
    cr_assert(LR0_itemeq(_in->i, i));
}

Test(testlist, testhaskey)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i2);
    LR0_ItemNode h = LR0_list();
    
    LR0_add(in, &h);
    LR0_add(in2, &h);

    cr_assert(LR0_haskey("key1", h));
    cr_assert(LR0_haskey("key2", h));
    cr_assert(!LR0_haskey("key", h));
}