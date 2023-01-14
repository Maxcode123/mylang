#include "symtable.h"

SymTable ST_symtable() {
    SymTable st = (SymTable)malloc(sizeof(struct _SymTable));
    st->head = lst_list();
    return st;
}

void ST_get(SymTable st, key k, SymTableItem *i) {
    Node in = lst_get(k, st->head);
    if (in == NULL)
    {
        *i = NULL;
        return;
    }
    *i = in->i;
}

void ST_getnode(SymTable st, key k, Node *in) {
    *in = lst_get(k, st->head);
}

bool ST_haskey(SymTable st, key k) {
    return lst_haskey(k, st->head);
}

void ST_put(SymTable st, Node in) {
    if (lst_haskey(in->k, st->head)) return;
    lst_add(in, (Node*)&st->head);
}

int ST_len(SymTable st) {
    return lst_len(st->head);
}

void ST_clear(SymTable st) {
    lst_clear((Node*)&st->head);
}

void ST_union(
    SymTable st1,
    SymTable st2,
    void (*hashf)(SymTableItem, key),
    Node after, 
    bool (*ieq)(SymTableItem, SymTableItem)
    ) {
    bool _flag; // true when add is used instead of insertat
    if (after == st1->head) _flag = true;
    Node n = st2->head;
    while (n != NULL) 
    {
        if (lst_haskey(n->k, st1->head)) 
        {
            n = n->next;
            continue;
        }
        Node in = ST_node(n->i, hashf);
        if (_flag) lst_add(in, &st1->head);
        else lst_insertat(&in, st1->head, &after, ieq);
        n = n->next;
    }
}

Node ST_node(SymTableItem i, void (*hashf)(SymTableItem, key)) {
    key hash = (char*)malloc(sizeof(char)*50);
    (*hashf)(i, hash);
    Node in = node(hash, i);
    return in;
}

void ST_print(SymTable st, void  (*printfn)(SymTableItem)) {
    Node n = st->head;
    while (n != NULL)
    {
        printfn(n->i);
        n = n->next;
    }
}

void ST_printk(SymTable st) {
    Node n = st->head;
    while (n != NULL)
    {
        printf("%s\n", n->k);
        n = n->next;
    }
}

void ST_printn(SymTable st, void (*printfn)(SymTableItem)) {
    Node n = st->head;
    while (n != NULL)
    {
        printf("%s: ", n->k);
        printfn(n->i);
        n = n->next;
    }
}