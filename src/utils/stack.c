#include "stack.h"

Stack stk_stack() {
    return lst_list();
}

Node stk_pop(Stack *sptr) {
    Node tmp = *sptr;
    if (tmp == NULL)
    {
        fprintf(stderr, "Cannot pop on empty stack.\n");
        exit(EXIT_FAILURE);
    }
    *sptr = tmp->next;
    return tmp;
}

void stk_push(Node n, Stack *sptr) {
    lst_add(n, sptr);
}

void stk_clear(Stack *sptr) {
    lst_clear(sptr);
}

int stk_len(Stack s) {
    return lst_len(s);
}

void stk_printk(Stack s) {
    Node n = s;
    printf("{ ");
    while (n != NULL)
    {
        printf("%s, ", n->k);
        n = n->next;
    }
    printf("} ");
}