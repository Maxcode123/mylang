#include <criterion/criterion.h>

#include "../src/parser/list.h"

Test(testlist, testinit)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    Node in = node("key1", i);
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

    Node in = node("key1", i);
    Node in2 = node("key1", i);
    Node in3 = node("key2", i);
    Node in4 = node("key1", i2);

    cr_assert(inodeeq(in, in2));
    cr_assert(!inodeeq(in, in3));
    cr_assert(!inodeeq(in, in4));
}

Test(testlist, testlistinit)
{
    Node in = list();
    cr_assert(in == NULL);
}

Test(testlist, testadd)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);

    Node in = node("key1", i);

    Node h = list();
    add(in, &h);
    cr_assert(strcmp(h->k, "key1") == 0);
    cr_assert(LR0_itemeq(h->i, i));
    cr_assert(h->next == NULL);

    Node in2 = node("key2", i);
    add(in2, &h);
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

    Node in = node("key1", i);
    Node in2 = node("key2", i);
    Node in3 = node("key3", i2);
    Node h = list();
    add(in, &h);
    add(in2, &h);
    add(in3, &h);

    Node _in = get("key1", h);
    cr_assert(inodeeq(_in, in));

    Node _in2 = get("key2", h);
    cr_assert(inodeeq(_in2, in2));

    Node _in3 = get("key3", h);
    cr_assert(inodeeq(_in3, in3));

    Node _in4 = get("asdas", h);
    cr_assert(_in4 == NULL);
}

Test(testlist, testsubs)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node h = list();
    add(in, &h);

    subs("key1", i2, h);
    Node _in = get("key1", h);
    cr_assert(LR0_itemeq(_in->i, i2));

    free(get("key1", h)->i);
    subs("key1", i, h);
    _in = get("key1", h);
    cr_assert(LR0_itemeq(_in->i, i));
}

Test(testlist, testhaskey)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);
    Node h = list();
    
    add(in, &h);
    add(in2, &h);

    cr_assert(haskey("key1", h));
    cr_assert(haskey("key2", h));
    cr_assert(!haskey("key", h));
}

Test(testlist, testclear)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);
    Node h = list();
    
    add(in, &h);
    add(in2, &h);

    cr_assert(h != NULL);
    clear(&h);
    cr_assert(h == NULL);
}

Test(testlist, testpop)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);
    Node h = list();
    
    add(in, &h);
    add(in2, &h);

    cr_assert(inodeeq(h, in2));
    pop(&h);
    cr_assert(inodeeq(h, in));
    pop(&h);
    cr_assert(h == NULL);   
}

Test(testlist, testinsert)
{
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 2);
    LR0_Item i3 = LR0_item(p, 1);

    Node in = node("key1", i);
    Node in2 = node("key2", i2);
    Node in3 = node("key3", i3);
    Node h = list();
    
    add(in, &h);
    add(in2, &h);
    
    cr_assert(inodeeq(h, in2));
    cr_assert(inodeeq(h->next, in));

    insert(&in3, &h);
    cr_assert(inodeeq(h, in2));
    cr_assert(inodeeq(h->next, in3));
    cr_assert(inodeeq(h->next->next, in));
}