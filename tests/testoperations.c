#include <criterion/criterion.h>

#include "../src/parser/operations.h"

Test(testoperations, testgetitems)
{
    SymTable st = stb_symtable();
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();

    LR0_getitems(S_NT_STM, st);
    cr_assert(stb_len(st) == 3);
    cr_assert(LR0_itemeq(((Node)st->head)->i, allitems[10]));
    cr_assert(LR0_itemeq(((Node)st->head)->next->i, allitems[6]));
    cr_assert(LR0_itemeq(((Node)st->head)->next->next->i, allitems[2]));

    SymTable st2 = stb_symtable();
    
    LR0_getitems(S_NT_EXPLIST, st2);
    cr_assert(stb_len(st2) == 6);
}

Test(testoperations, testclosure)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    SymTable I = stb_symtable();
    Node in = stb_node(allitems[4], &LR0_itemhash);

    stb_put(I, in);

    LR0_closure(I);

    cr_assert(stb_len(I) == 4);
}

Test(testoperations, testgoto)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    SymTable I = stb_symtable();
    SymTable G = stb_symtable();

    Node n1 = stb_node(allitems[4], &LR0_itemhash);
    Node n2 = stb_node(allitems[2], &LR0_itemhash);
    Node n3 = stb_node(allitems[6], &LR0_itemhash);
    Node n4 = stb_node(allitems[11], &LR0_itemhash);

    stb_put(I, n1);
    stb_put(I, n2);
    stb_put(I, n3);
    stb_put(I, n4);

    LR0_goto(I, S_NT_STM, G);

    cr_assert(stb_len(G) == 2);
}