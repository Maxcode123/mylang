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

void LR0_getitems(symbol X, LR0_Item *allitems, LR0_SymTable st) {
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