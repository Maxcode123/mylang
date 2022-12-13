#include "operations.h"

void LR0_closure(LR0_SymTable I) {
    LR0_ItemNode n = I->head;
    int _len, len_;
    while (n != NULL)
    {
        if (n->i->before != -1) // dot is not last symbol
        {
            
        }
        n = n->next;
    }
}

void LR0_getitems(symbol X, LR0_SymTable st) {
    for (int i = 0; i < ITEMS; i++)
    {
        if (LR0_allitems[i]->p->lhs != X) continue;
        if (LR0_allitems[i]->before == 0) 
        {
            LR0_ItemNode in = LR0_ST_node(LR0_allitems[i]);
            LR0_ST_put(st, in);
        }
    }
}