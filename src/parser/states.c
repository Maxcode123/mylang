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

void printedge(Edge e) {
    key hash = malloc(sizeof(char)*50);
    statehash(e->from, hash);
    printf("%s -> ", hash);
    statehash(e->to, hash);
    printf("%s, ", hash);
    char **symbols = getsymbols();
    printf("%s\n", symbols[e->X-10]);
}

void stateinit(StateSet T) {
    LR0_Item *allitems = LR0_getallitems();
    State init = ST_symtable();

    ST_put(init, ST_node(allitems[0], LR0_itemhash));
    LR0_closure(init);
    
    ST_put(T, ST_node(init, &statehash));
}

void states(StateSet T, EdgeSet E) {
    stateinit(T);
    StateNode SN = T->head;
    int lenT, lenE;
    symbol X;
    StateSet tmp = ST_symtable(); // set used to host state J, { J }

    while (SN != NULL) // loop on states
    {
        ItemNode in = ((State)(SN->i))->head;
        lenT = ST_len(T), lenE = ST_len(E);
        while (in != NULL) // loop on state items
        {
            if (((LR0_Item)in->i)->before == -1) {in = in->next; continue;}

            State J = ST_symtable();
            X = ((LR0_Item)in->i)->p->rhs[((LR0_Item)in->i)->before];
            LR0_goto((State)(SN->i), X, J);
            
            ST_put(tmp, ST_node(J, &statehash));
            ST_union(T, tmp, &statehash); // union to insert states after head
            ST_clear(tmp);

            Edge e = edge(X, (State)(SN->i), J);
            ST_put(E, ST_node(e, &edgehash));
            
            in = in->next;
        }
        if (lenT == ST_len(T) & lenE == ST_len(E)) {free(tmp); return;}
        SN = SN->next;        
    }    
}

void statehash(State I, key hash) {
    int i[ST_len(I)];
    int c = 0;
    Node n = I->head;
    while (n != NULL)
    {
        i[c++] = LR0_getindex((LR0_Item)n->i);
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

void printstate(State I) {
    ST_print(I, &printit);
}