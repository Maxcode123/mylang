#include <criterion/criterion.h>

#include "../src/parser/list.h"

Test(testlist, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);

    ItemNode in = node("key1", i);
    cr_assert(strcmp(in->k, "key1") == 0);
    cr_assert(itemeq(in->i, i));
    cr_assert(in->next == NULL);
}

Test(testlist, testinodeeq)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);
    Item i2 = item(p, 2);

    ItemNode in = node("key1", i);
    ItemNode in2 = node("key1", i);
    ItemNode in3 = node("key2", i);
    ItemNode in4 = node("key1", i2);

    cr_assert(inodeeq(in, in2));
    cr_assert(!inodeeq(in, in3));
    cr_assert(!inodeeq(in, in4));
}

Test(testlist, testlistinit)
{
    ItemNode in = list();
    cr_assert(in == NULL);
}

Test(testlist, testadd)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);

    ItemNode in = node("key1", i);

    ItemNode h = list();
    add(in, &h);
    cr_assert(strcmp(h->k, "key1") == 0);
    cr_assert(itemeq(h->i, i));
    cr_assert(h->next == NULL);

    ItemNode in2 = node("key2", i);
    add(in2, &h);
    cr_assert(strcmp(h->k, "key2") == 0);
    cr_assert(itemeq(h->i, i));
    cr_assert(h->next == in);
}

Test(testlist, testget)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);
    Item i2 = item(p, 2);

    ItemNode in = node("key1", i);
    ItemNode in2 = node("key2", i);
    ItemNode in3 = node("key3", i2);
    ItemNode h = list();
    add(in, &h);
    add(in2, &h);
    add(in3, &h);

    ItemNode _in = get("key1", h);
    cr_assert(inodeeq(_in, in));

    ItemNode _in2 = get("key2", h);
    cr_assert(inodeeq(_in2, in2));

    ItemNode _in3 = get("key3", h);
    cr_assert(inodeeq(_in3, in3));
}

Test(testlist, testsubs)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    Item i = item(p, 0);
    Item i2 = item(p, 2);

    ItemNode in = node("key1", i);
    ItemNode h = list();
    add(in, &h);

    subs("key1", i2, h);
    ItemNode _in = get("key1", h);
    cr_assert(itemeq(_in->i, i2));

    subs("key1", i, h);
    _in = get("key1", h);
    cr_assert(itemeq(_in->i, i));
}