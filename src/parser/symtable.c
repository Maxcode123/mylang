#include "symtable.h"

SymTable symtable() {
    SymTable st = (SymTable)malloc(sizeof(struct _SymTable));
    st->head = list();
    return st;
}

void get(SymTable st, key k, Item *i) {
    ItemNode in = getin(k, st->head);
    if (in == NULL) 
    {
        *i = NULL;
        return;
    }
    *i = in->i;
}

void put(SymTable st, key k, Item i) {
    if (subs(k, i, st->head)) return;
    ItemNode in = node(k, i);
    addin(in, &st->head);
}
