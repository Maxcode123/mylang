#include "symtable.h"

SymTable ST_symtable() {
    SymTable st = (SymTable)malloc(sizeof(struct _SymTable));
    st->head = list();
    return st;
}

void ST_get(SymTable st, key k, LR0_Item *i) {
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

Node ST_node(LR0_Item i) {
    key hash = (char*)malloc(sizeof(char)*50);
    LR0_itemhash(i, hash);
    Node in = node(hash, i);
    return in;
}

void ST_clear(SymTable st) {
    clear((Node*)&st->head);
}

void ST_union(SymTable st1, SymTable st2) {
    Node n = st2->head;
    while (n != NULL) 
    {
        if (haskey(n->k, st1->head)) 
        {
            n = n->next;
            continue;
        }
        Node in = ST_node(n->i);
        insert(&in, (Node*)&(st1->head));
        n = n->next;
    }
}