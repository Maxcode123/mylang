#include "list.h"

ItemNode node(key k, Item i) {
    ItemNode n = (ItemNode)malloc(sizeof(struct _ItemNode));
    n->k = k;
    n->i = i;
    n->next = NULL;
    return n;
}

bool inodeeq(ItemNode in1, ItemNode in2) {
    if (strcmp(in1->k, in2->k) != 0) return false;
    if (!itemeq(in1->i, in2->i)) return false;
    if (in1->next != in2->next) return false;
    return true;
}

ItemNode list() {
    return NULL;
}

void add(ItemNode n, ItemNode* headptr) {
    if (*headptr == NULL)
    {
        *headptr = n;
        n->next = NULL;
    }
    else
    {
        n->next = *headptr;
        *headptr = n;
    }
}

ItemNode get(key k, ItemNode head) {
    ItemNode n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return n;
        n = n->next;
    }
    return NULL;
}

bool subs(key k, Item i, ItemNode head)
{
    ItemNode n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0)
        {
            n->i = i;
            return true;
        }
        n = n->next;
    }
    return false;
}