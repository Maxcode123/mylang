#include <stdio.h>

#include "../src/parser/automaton.h"


void main() {
    LR0_inititems();
    StateSet T = ST_symtable();
    EdgeSet E = ST_symtable();

    states(T, E);
    initptable(T);
    shifts(E);
}

void printstates() {
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    StateSet T = ST_symtable();
    EdgeSet E = ST_symtable();

    states(T, E);
    Node n = T->head;
    int i = 0;
    while (n != NULL)
    {
        printf("\nstate %d (hash: %s):\n", i++, n->k);
        printstate((State)(n->i));
        n = n->next;
    }
    printf("\nEdges: {source-state hash} -> {target-state hash}, {symbol}\n");

    n = E->head;
    i = 0;
    while (n != NULL)
    {
        printedge((Edge)(n->i));
        n = n->next;
    }
}