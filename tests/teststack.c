#include <criterion/criterion.h>

#include "../src/utils/stack.h"

Test(teststack, testinit)
{
    Stack s = stk_stack();
    cr_assert(s == NULL);
}

Test(teststack, testpush)
{
    Stack s = stk_stack();
    int *i = malloc(sizeof(*i));
    *i = 5;
    Node n1 = node("key", i);
    char *j = malloc(sizeof(*j)*10);
    j = "value";
    Node n2 = node("key2", j);
    stk_push(n1, &s);
    stk_push(n2, &s);
    cr_assert(strcmp(s->i, "value") == 0);
    cr_assert(*(int*)s->next->i == 5);
}

Test(teststack, testpop)
{
    Stack s = stk_stack();
    int *i = malloc(sizeof(*i));
    *i = 5;
    Node n1 = node("key", i);
    char *j = malloc(sizeof(*j)*10);
    j = "value";
    Node n2 = node("key2", j);
    stk_push(n1, &s);
    stk_push(n2, &s);

    stk_pop(&s);
    cr_assert(*(int*)s->i == 5);

    stk_pop(&s);
    cr_assert(s == NULL);
}

Test(teststack, testclear)
{
    Stack s = stk_stack();
    int *i = malloc(sizeof(*i));
    *i = 5;
    Node n1 = node("key", i);
    char *j = malloc(sizeof(*j)*10);
    j = "value";
    Node n2 = node("key2", j);
    stk_push(n1, &s);
    stk_push(n2, &s);

    stk_clear(&s);
    cr_assert(s == NULL);
}

Test(teststack, testlen)
{
    Stack s = stk_stack();
    int *i = malloc(sizeof(*i));
    *i = 5;
    Node n1 = node("key", i);
    char *j = malloc(sizeof(*j)*10);
    j = "value";
    Node n2 = node("key2", j);
    stk_push(n1, &s);
    cr_assert(stk_len(s) == 1);
    stk_push(n2, &s);
    cr_assert(stk_len(s) == 2);
}