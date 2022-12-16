#include "symtable.h"

SymTable ST_symtable() {
    SymTable st = (SymTable)malloc(sizeof(struct _SymTable));
    st->head = list();
    return st;
}

void ST_get(SymTable st, key k, void **i) {
    Node in = get(k, st->head);
    if (in == NULL)
    {
        *i = NULL;
        return;
    }
    *i = in->i;
}

void ST_put(SymTable st, Node in) {
    if (haskey(in->k, st->head)) return;
    add(in, (Node*)&st->head);
}

int ST_len(SymTable st) {
    Node n = st->head;
    int c = 0;
    while (n != NULL)
    {
        c++;
        n = n->next;
    }
    return c;
}

void ST_clear(SymTable st) {
    clear((Node*)&st->head);
}

void ST_union(SymTable st1, SymTable st2, void (*hashf)(void *, key)) {
    Node n = st2->head;
    while (n != NULL) 
    {
        if (haskey(n->k, st1->head)) 
        {
            n = n->next;
            continue;
        }
        Node in = ST_node(n->i, hashf);
        insert(&in, (Node*)&(st1->head));
        n = n->next;
    }
}

Node ST_node(void *i, void (*hashf)(void *, key)) {
    key hash = (char*)malloc(sizeof(char)*50);
    (*hashf)(i, hash);
    Node in = node(hash, i);
    return in;
}