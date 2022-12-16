#include "operations.h"

void LR0_O_closure(SymTable I) {
    LR0_ItemNode n = I->head;
    SymTable st = ST_symtable();
    int _len, len_;
    symbol X;
    while ( n != NULL)
    {
        if (((LR0_Item)n->i)->before != -1) // dot is not last symbol
        {
            X = ((LR0_Item)n->i)->p->rhs[((LR0_Item)n->i)->before];
            LR0_O_getitems(X, st);
            _len = ST_len(I);
            ST_union(I, st);
            len_ = ST_len(I);
            ST_clear(st);
            if (_len == len_)
            {
                free(st);
                return;
            } 
        }
        n = n->next;
    }
}

void LR0_O_getitems(symbol X, SymTable st) {
    LR0_Item *allitems = LR0_getallitems();
    for (int i = 0; i < ITEMS; i++)
    {
        if (allitems[i]->p->lhs != X) continue;
        if (allitems[i]->before == 0) 
        {
            LR0_ItemNode in = ST_node(allitems[i]);
            ST_put(st, in);
        }
    }
}

void LR0_O_goto(SymTable I, LR0_Item X, SymTable G) {
    LR0_ItemNode n = I->head;
    int i;
    LR0_Item item;
    LR0_Item *allitems = LR0_getallitems();
    while (n != NULL)
    {
        if (((LR0_Item)n->i)->before == -1)
        {
            n = n->next;
            continue;
        }
        i = LR0_getindex(n->i);
        item = allitems[i+1];
        LR0_ItemNode in = ST_node(item);
        ST_put(G, in);
        n = n->next;
    }
    LR0_O_closure(G);
}