#include "list.h"

Node node(key k, ListItem i) {
    Node n = (Node)malloc(sizeof(struct _Node));
    n->k = k;
    n->i = i;
    n->next = NULL;
    return n;
}

bool lnodeeq(Node in1, Node in2, bool (*ieq)(ListItem, ListItem)) {
    if (in1->next != in2->next) return false;
    if (!nodeeq(in1, in2, ieq)) return false;
    return true;
}

bool nodeeq(Node in1 , Node in2, bool (*ieq)(ListItem, ListItem)) {
    if (strcmp(in1->k, in2->k) != 0) return false;
    if (!(*ieq)(in1->i, in2->i)) return false;
    return true;
}

Node lst_list() {
    return NULL;
}

void lst_add(Node n, Node* headptr) {
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

Node lst_get(key k, Node head) {
    Node n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return n;
        n = n->next;
    }
    return NULL;
}

bool lst_subs(key k, ListItem i, Node head) {
    Node n = head;
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

bool lst_haskey(key k, Node head) {
    Node n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return true;
        n = n->next;
    }
    return false;
}

void lst_clear(Node *headptr) {
    while (*headptr != NULL) lst_pop(headptr);
}

void lst_pop(Node *headptr) {
    Node tmp = (*headptr)->next;
    free(*headptr);
    *headptr = tmp;
}

void lst_insert(Node *nptr, Node *headptr) {
    (*nptr)->next = (*headptr)->next;
    (*headptr)->next = *nptr;
}

void lst_insertat(Node *nptr, Node head, Node *n, bool (*ieq)(ListItem, ListItem)) {
    Node tmp = head;
    while (tmp != NULL)
    {
        if (nodeeq(tmp, *n, ieq))
        {
            (*nptr)->next = (*n)->next;
            (*n)->next = *nptr;
            return;
        }
        tmp = tmp->next;
    }
}

int lst_len(Node head) {
    Node n = head;
    int c = 0;
    while (n != NULL)
    {
        c++;
        n = n->next;
    }
    return c;
}