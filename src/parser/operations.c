#include "operations.h"

void LR0_closure(SymTable I) {
    ItemNode n = I->head;
    SymTable st = ST_symtable();
    symbol X;
    while ( n != NULL)
    {
        if (((LR0_Item)n->i)->before != -1) // dot is not last symbol
        {
            X = ((LR0_Item)n->i)->p->rhs[((LR0_Item)n->i)->before];
            LR0_getitems(X, st);
            if (ST_len(st) == 0) {n = n->next; continue;}
            ST_union(I, st, &LR0_itemhash, n, &LR0_itemeq);
            ST_clear(st);
        }
        n = n->next;
    }
    free(st);
}

void LR0_getitems(symbol X, SymTable st) {
    LR0_Item *allitems = LR0_getallitems();
    for (int i = 0; i < ITEMS; i++)
    {
        if (allitems[i]->p->lhs != X) continue;
        if (allitems[i]->before == 0) 
        {
            ItemNode in = ST_node(allitems[i], &LR0_itemhash);
            ST_put(st, in);
        }
    }
}

void LR0_goto(SymTable I, symbol X, SymTable G) {
    ItemNode n = I->head;
    int i;
    LR0_Item *allitems = LR0_getallitems();
    while (n != NULL)
    {
        if (
            ((LR0_Item)n->i)->before == -1 ||
            ((LR0_Item)n->i)->p->rhs[((LR0_Item)n->i)->before] != X
            )
        {
            n = n->next;
            continue;
        }
        i = LR0_getindex((LR0_Item)(n->i));
        ItemNode in = ST_node(allitems[i+1], &LR0_itemhash);
        ST_put(G, in);
        n = n->next;
    }
    LR0_closure(G);
}
