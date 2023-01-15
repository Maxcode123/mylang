#include "operations.h"

void LR0_closure(ItemSet I) {
    ItemNode n = I->head;
    SymTable st = stb_symtable();
    symbol X;
    while ( n != NULL)
    {
        if (((LR0_Item)n->i)->before != -1) // dot is not last symbol
        {
            X = ((LR0_Item)n->i)->p->rhs[((LR0_Item)n->i)->before];
            LR0_getitems(X, st);
            if (stb_len(st) == 0) {n = n->next; continue;}
            stb_union(I, st, &LR0_itemhash, n, &LR0_itemeq);
            stb_clear(st);
        }
        n = n->next;
    }
    free(st);
}

void LR0_getitems(symbol X, ItemSet st) {
    Production *p = getprods();
    for (int j = 0; j < PRODUCTIONS; j++)
    {
        if (p[j]->lhs == X && p[j]->len == 1 && !IS_TERMINAL(p[j]->rhs[0])) 
        {
            LR0_getitems(p[j]->rhs[0], st);
        }
    }
    LR0_Item *allitems = LR0_getallitems();
    for (int i = 0; i < ITEMS; i++)
    {
        if (allitems[i]->p->lhs != X) continue;
        if (allitems[i]->before == 0) 
        {
            ItemNode in = stb_node(allitems[i], &LR0_itemhash);
            stb_put(st, in);
        }
    }
}

void LR0_goto(ItemSet I, symbol X, ItemSet G) {
    ItemNode n = I->head;
    int i;
    LR0_Item *allitems = LR0_getallitems();
    while (n != NULL)
    {
        if (
            ((LR0_Item)n->i)->before == -1 || // dot in end
            ((LR0_Item)n->i)->p->rhs[((LR0_Item)n->i)->before] != X // dot is not before X
        )
        {
            n = n->next;
            continue;
        }
        i = LR0_getindex((LR0_Item)(n->i));
        ItemNode in = stb_node(allitems[i+1], &LR0_itemhash);
        stb_put(G, in);
        n = n->next;
    }
    LR0_closure(G);
}
