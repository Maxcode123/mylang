#include "symtable.h"

SymTable LR0_ST_symtable() {
    SymTable st = (SymTable)malloc(sizeof(struct _SymTable));
    st->head = LR0_list();
    return st;
}

void LR0_ST_get(SymTable st, key k, LR0_Item *i) {
    LR0_ItemNode in = LR0_get(k, st->head);
    if (in == NULL)
    {
        *i = NULL;
        return;
    }
    *i = in->i;
}

void LR0_ST_put(SymTable st, LR0_ItemNode in) {
    if (LR0_haskey(in->k, st->head)) return;
    LR0_add(in, (LR0_ItemNode*)&st->head);
}

int LR0_ST_len(SymTable st) {
    LR0_ItemNode n = st->head;
    int c = 0;
    while (n != NULL)
    {
        c++;
        n = n->next;
    }
    return c;
}

LR0_ItemNode LR0_ST_node(LR0_Item i) {
    key hash = (char*)malloc(sizeof(char)*50);
    LR0_itemhash(i, hash);
    LR0_ItemNode in = LR0_node(hash, i);
    return in;
}

void LR0_ST_clear(SymTable st) {
    LR0_clear((LR0_ItemNode*)&st->head);
}

void LR0_ST_union(SymTable st1, SymTable st2) {
    LR0_ItemNode n = st2->head;
    while (n != NULL) 
    {
        if (LR0_haskey(n->k, st1->head)) 
        {
            n = n->next;
            continue;
        }
        LR0_ItemNode in = LR0_ST_node(n->i);
        LR0_insert(&in, (LR0_ItemNode*)&(st1->head));
        n = n->next;
    }
}