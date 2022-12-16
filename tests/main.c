#include <stdio.h>

#include "../src/parser/operations.h"


int main() {
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    SymTable I = ST_symtable();
    SymTable G = ST_symtable();

    Node n1 = ST_node(allitems[4], &LR0_itemhash);
    Node n2 = ST_node(allitems[2], &LR0_itemhash);
    Node n3 = ST_node(allitems[6], &LR0_itemhash);
    Node n4 = ST_node(allitems[11], &LR0_itemhash);

    ST_put(I, n1);
    ST_put(I, n2);
    ST_put(I, n3);
    ST_put(I, n4);

    LR0_O_goto(I, S_NT_STM, G);

    Node h = G->head;
    while (h != NULL)
    {
        printit(h->i);
        h = h->next;
    }
}