#include "list.h"

Node node(key k, void *i) {
    Node n = (Node)malloc(sizeof(struct _Node));
    n->k = k;
    n->i = i;
    n->next = NULL;
    return n;
}

bool inodeeq(Node in1, Node in2) {
    if (in1->next != in2->next) return false;
    if (!ninodeeq(in1, in2)) return false;
    return true;
}

bool ninodeeq(Node in1 , Node in2) {
    if (strcmp(in1->k, in2->k) != 0) return false;
    if (!LR0_itemeq(in1->i, in2->i)) return false;
    return true;
}

Node list() {
    return NULL;
}

void add(Node n, Node* headptr) {
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

Node get(key k, Node head) {
    Node n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return n;
        n = n->next;
    }
    return NULL;
}

bool subs(key k, void *i, Node head) {
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

bool haskey(key k, Node head) {
    Node n = head;
    while (n != NULL)
    {
        if (strcmp(n->k, k) == 0) return true;
        n = n->next;
    }
    return false;
}

void clear(Node *headptr) {
    while (*headptr != NULL) pop(headptr);
}

void pop(Node *headptr) {
    Node tmp = (*headptr)->next;
    free(*headptr);
    *headptr = tmp;
}

void insert(Node *nptr, Node *headptr) {
    (*nptr)->next = (*headptr)->next;
    (*headptr)->next = *nptr;
}