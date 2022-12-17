#include "states.h"

Edge edge(symbol X, State from, State to) {
    Edge e = (Edge)malloc(sizeof(struct _Edge));
    e->X = X;
    e->from = from;
    e->to = to;
    return e;
}

void edgehash(Edge e, key hash) {
    statehash(e->from, hash);
    char *buff = malloc(sizeof(char)*50);
    statehash(e->to, buff);
    strcat(hash, buff);
    sprintf(buff, "%d", e->X);
    strcat(hash, buff);
    free(buff);
}

void stateinit(SymTable T) {
    LR0_Item *allitems = LR0_getallitems();
    State init = ST_symtable();

    ST_put(init, ST_node(allitems[0], LR0_itemhash));
    LR0_closure(init);
    
    ST_put(T, ST_node(init, &statehash));
}

void states(SymTable T, SymTable E) {
    stateinit(T);
    Node t = T->head;

    while (t != NULL) // loop on states
    {
        Node i = ((SymTable)(t->i))->head;
        while (i != NULL) // loop on state items
        {
            if (((LR0_Item)i->i)->before == -1)
            {
                i = i->next;
                continue;
            }
            SymTable J = ST_symtable();
            LR0_goto(t, ((LR0_Item)i->i)->p->rhs[((LR0_Item)i->i)->before], J);
            ST_put(T, ST_node(J, &statehash));
            i = i->next;
        }
        t = t->next;        
    }    
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
    sorti(i, ST_len(I));
    char *buff = (char*)malloc(sizeof(char)*3);
    sprintf(hash, "%d", i[0]);
    for (int j = 1; j < ST_len(I); j++)
    {
        sprintf(buff, "%d", i[j]);
        strcat(hash, buff);
    }
    free(buff);
}