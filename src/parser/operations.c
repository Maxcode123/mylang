#include "operations.h"

void LR0_O_closure(LR0_SymTable I) {
    LR0_ItemNode n = I->head;
    LR0_SymTable st = LR0_ST_symtable();
    int _len, len_;
    symbol X;
    while ( n != NULL)
    {
        if (n->i->before != -1) // dot is not last symbol
        {
            X = n->i->p->rhs[n->i->before];
            LR0_O_getitems(X, st);
            _len = LR0_ST_len(I);
            LR0_ST_union(I, st);
            len_ = LR0_ST_len(I);
            LR0_ST_clear(st);
            if (_len == len_)
            {
                free(st);
                return;
            } 
        }
        n = n->next;
    }
}

void LR0_O_getitems(symbol X, LR0_SymTable st) {
    LR0_Item *allitems = LR0_getallitems();
    for (int i = 0; i < ITEMS; i++)
    {
        if (allitems[i]->p->lhs != X) continue;
        if (allitems[i]->before == 0) 
        {
            LR0_ItemNode in = LR0_ST_node(allitems[i]);
            LR0_ST_put(st, in);
        }
    }
}

void LR0_O_goto(LR0_SymTable I, LR0_Item X, LR0_SymTable G) {
    LR0_ItemNode n = I->head;
    int i;
    LR0_Item item;
    LR0_Item *allitems = LR0_getallitems();
    while (n != NULL)
    {
        if (n->i->before == -1)
        {
            n = n->next;
            continue;
        }
        i = LR0_getindex(n->i);
        item = allitems[i+1];
        LR0_ItemNode in = LR0_ST_node(item);
        LR0_ST_put(G, in);
        n = n->next;
    }
    LR0_O_closure(G);
}