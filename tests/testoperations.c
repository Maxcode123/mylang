#include <criterion/criterion.h>

#include "../src/parser/operations.h"

Test(testoperations, testgetitems)
{
    SymTable st = ST_symtable();
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();

    LR0_getitems(S_NT_STM, st);
    cr_assert(ST_len(st) == 3);
    cr_assert(LR0_itemeq(((Node)st->head)->i, allitems[10]));
    cr_assert(LR0_itemeq(((Node)st->head)->next->i, allitems[6]));
    cr_assert(LR0_itemeq(((Node)st->head)->next->next->i, allitems[2]));
}

Test(testoperations, testclosure)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    SymTable I = ST_symtable();
    Node in = ST_node(allitems[4], &LR0_itemhash);

    ST_put(I, in);

    LR0_closure(I);

    cr_assert(ST_len(I) == 4);
}

Test(testoperations, testgoto)
{
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

    LR0_goto(I, S_NT_STM, G);

    cr_assert(ST_len(G) == 2);
}