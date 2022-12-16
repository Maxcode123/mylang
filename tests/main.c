#include <stdio.h>

#include "../src/parser/operations.h"


int main() {
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();


    for (int i = 0; i <ITEMS; i++)
    {
        printprod(allitems[i]->p);
    }

    
    // printf("before: %d, lhs: %d, len: %d, rhs[0]: %d,\n", allitems[15]->before, allitems[15]->p->lhs, allitems[15]->p->len, allitems[15]->p->rhs[0]);
    
}