#include "list.h"

LR0_ItemNode LR0_node(key k, LR0_Item i) {
    LR0_ItemNode n = (LR0_ItemNode)malloc(sizeof(struct _LR0_ItemNode));
    n->k = k;
    n->i = i;
    n->next = NULL;
    return n;
}

bool LR0_inodeeq(LR0_ItemNode in1, LR0_ItemNode in2) {
    if (strcmp(in1->k, in2->k) != 0) return false;
    if (!LR0_itemeq(in1->i, in2->i)) return false;
    if (in1->next != in2->next) return false;
    return true;
}

LR0_ItemNode LR0_list() {
    return NULL;
}

void LR0_add(LR0_ItemNode n, LR0_ItemNode* headptr) {
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

LR0_ItemNode LR0_get(key k, LR0_ItemNode head) {
    LR0_ItemNode n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return n;
        n = n->next;
    }
    return NULL;
}

bool LR0_subs(key k, LR0_Item i, LR0_ItemNode head) {
    LR0_ItemNode n = head;
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

bool LR0_haskey(key k, LR0_ItemNode head) {
    LR0_ItemNode n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return true;
        n = n->next;
    }
    return false;
}