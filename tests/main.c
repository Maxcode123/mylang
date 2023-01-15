#include <stdio.h>

#include "../src/parser/parser.h"
#include "../src/parser/automaton.h"
#include "../src/parser/adapter.h"


void main(int argc, char **argv) {
    Token *ta = scan(argv[1]);
    AST t = parse(ta);

    // printparsetable();
    // printstates();

    // LR0_inititems();
    // StateSet T = stb_symtable();
    // EdgeSet E = stb_symtable();
    // states(T, E);

    // State J = stb_symtable();
    // symbol X;

    // StateNode SN = T->head;

    // while (SN != NULL)
    // {
    //     if (strcmp(SN->k, "12151719232933") == 0)
    //     {
    //         ItemNode in = ((State)(SN->i))->head;
    //         while (in != NULL)
    //         {
    //             printf("\nstate I: \n");
    //             printstate((State)SN->i);
    //             printf("\nitem: ");
    //             printit((LR0_Item)in->i);
    //             X = ((LR0_Item)in->i)->p->rhs[((LR0_Item)in->i)->before];
    //             LR0_goto((State)(SN->i), X, J);
    //             printf("\nGOTO(I,X(%d)): \n", X);
    //             printstate(J);
    //             in = in->next;
    //         }
    //     }
    //     SN = SN->next;
    // }

}

void printparsetable() {
    LR0_inititems();
    StateSet T = stb_symtable();
    EdgeSet E = stb_symtable();

    states(T, E);
    initptable(T);
    shiftgoto(E);
    reduces(T);

    char **s = getsymbols();
    StateActionsMap *pt = getptable();
    for (int i = 0; i < SYMBOLS; i++) {
        printf("\nSYMBOL: %s\n", s[i]);
        stb_printn(pt[i], &printactlst);
    }
}

void printstates() {
    LR0_inititems();
    StateSet T = stb_symtable();
    EdgeSet E = stb_symtable();

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