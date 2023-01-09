#include <stdio.h>

#include "../src/parser/automaton.h"


void main() {
    LR0_inititems();
    SymbolSet S = ST_symtable();
    first(S_NT_BINOP, S);
    ST_printk(S);
}

void printparsetable() {
    LR0_inititems();
    StateSet T = ST_symtable();
    EdgeSet E = ST_symtable();

    states(T, E);
    initptable(T);
    shiftgoto(E);
    reduces(T);

    char **s = getsymbols();
    StateActionsMap *pt = getptable();
    for (int i = 0; i < SYMBOLS; i++) {
        printf("\nSYMBOL: %s\n", s[i]);
        ST_printn(pt[i], &printactlst);
    }
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