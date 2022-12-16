#include "states.h"

Edge edge(symbol X, State from, State to) {
    Edge e = (Edge)malloc(sizeof(struct _Edge));
    e->X = X;
    e->from = from;
    e->to = to;
    return e;
}

void states(SymTable T, SymTable E) {
    LR0_Item *allitems = LR0_getallitems();
    State init = ST_symtable();
    Node n = ST_node(allitems[0], LR0_itemhash);
    ST_put(init, n);
    LR0_closure(init);
    // ST_put()
}

void statehash(State I, key hash) {
    int i[ST_len(I)];
    int c = 0;
    Node n = I->head;
    while (n != NULL)
    {
        i[c] = LR0_getindex((LR0_Item)n->i);
        c++;
        n = n->next;
    }
    // sort i
    char *buff = (char*)malloc(sizeof(char)*3);
    sprintf(hash, "%d", i[0]);
    for (int j = 1; j < ST_len(I); j++)
    {
        sprintf(buff, "%d", i[j]);
        strcat(hash, buff);
    }
    free(buff);
}