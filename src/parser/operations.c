#include "operations.h"

void LR0_O_closure(LR0_SymTable I) {
    LR0_ItemNode n = I->head;
    LR0_SymTable items = LR0_ST_symtable();
    int _len, len_;
    symbol X;
    while ( n != NULL)
    {
        if (n->i->before != -1) // dot is not last symbol
        {
            X = n->i->p->rhs[n->i->before];
            LR0_O_getitems(X, items);
            _len = LR0_ST_len(I);
            // update(I, items)
            len_ = LR0_ST_len(I);
            LR0_ST_clear(items);
            if (_len == len_)
            {
                free(items);
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
