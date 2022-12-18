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

void stateinit(StateSet T) {
    LR0_Item *allitems = LR0_getallitems();
    State init = ST_symtable();

    ST_put(init, ST_node(allitems[0], LR0_itemhash));
    LR0_closure(init);
    
    ST_put(T, ST_node(init, &statehash));
}

void states(StateSet T, EdgeSet E) {
    stateinit(T);
    StateNode IN = T->head;
    int _lenT, lenT_, _lenE, lenE_;
    symbol X;

    while (IN != NULL) // loop on states
    {
        ItemNode in = ((State)(IN->i))->head;
        while (in != NULL) // loop on state items
        {
            if (((LR0_Item)in->i)->before == -1)
            {
                in = in->next;
                continue;
            }
            State J = ST_symtable();
            X = ((LR0_Item)in->i)->p->rhs[((LR0_Item)in->i)->before];
            LR0_goto((State)(IN->i), X, J);

            _lenT = ST_len(T);
            ST_put(T, ST_node(J, &statehash));
            lenT_ = ST_len(T);

            Edge e = edge(X, (State)(IN->i), J);

            _lenE = ST_len(E);
            ST_put(E, ST_node(e, &edgehash));
            lenE_ = ST_len(E);
            if (_lenT == lenT_ && _lenE == lenE_) return;
            in = in->next;
        }
        IN = IN->next;        
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