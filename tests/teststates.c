#include <criterion/criterion.h>

#include "../src/parser/states.h"

Test(teststates, testedgeinit)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    State I1 = stb_symtable();
    State I2 = stb_symtable();

    Node n1 = stb_node(allitems[4], &LR0_itemhash);
    Node n2 = stb_node(allitems[2], &LR0_itemhash);
    
    Node n3 = stb_node(allitems[6], &LR0_itemhash);
    Node n4 = stb_node(allitems[11], &LR0_itemhash);

    stb_put(I1, n1);
    stb_put(I1, n2);
    
    stb_put(I2, n3);
    stb_put(I2, n4);

    Edge e = edge(S_T_MINUS, I1, I2);
    cr_assert(e->X == S_T_MINUS);
    cr_assert(e->from->head == I1->head);
    cr_assert(e->to->head == I2->head);
}

Test(teststates, testedgehash)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    State I1 = stb_symtable();
    State I2 = stb_symtable();

    Node n1 = stb_node(allitems[4], &LR0_itemhash);
    Node n2 = stb_node(allitems[2], &LR0_itemhash);
    
    Node n3 = stb_node(allitems[6], &LR0_itemhash);
    Node n4 = stb_node(allitems[11], &LR0_itemhash);

    stb_put(I1, n1);
    stb_put(I1, n2);
    
    stb_put(I2, n3);
    stb_put(I2, n4);

    Edge e = edge(S_T_MINUS, I1, I2);
    key hash = malloc(sizeof(char)*50);
    edgehash(e, hash);
    cr_assert(strcmp(hash, "2461120") == 0);
}

Test(teststates, teststatehash)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    State I = stb_symtable();

    Node n1 = stb_node(allitems[4], &LR0_itemhash);
    Node n2 = stb_node(allitems[2], &LR0_itemhash);
    Node n3 = stb_node(allitems[29], &LR0_itemhash);
    
    stb_put(I, n1);
    stb_put(I, n2);
    stb_put(I, n3);

    key hash = malloc(sizeof(char)*50);
    statehash(I, hash);
    cr_assert(strcmp(hash, "2429") == 0);

    State I2 = stb_symtable();

    stb_put(I2, n3);
    stb_put(I2, n1);
    stb_put(I2, n2);

    cr_assert(I2->head != I->head);

    key hash2 = malloc(sizeof(char)*50);
    statehash(I2, hash2);
    cr_assert(strcmp(hash, hash2) == 0);
}

Test(teststates, teststateinit)
{
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    SymTable T = stb_symtable();
    stateinit(T);
    cr_assert(LR0_itemeq((LR0_Item)((Node)((State)((Node)(T->head))->i)->head)->i, allitems[2]));
}