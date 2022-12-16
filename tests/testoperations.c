#include <criterion/criterion.h>

#include "../src/parser/grammar.h"
#include "../src/parser/operations.h"

Test(testoperations, testgetitems)
{
    SymTable st = ST_symtable();
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();

    LR0_O_getitems(S_NT_STM, st);
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
    Node in = ST_node(allitems[4]);

    ST_put(I, in);

    LR0_O_closure(I);

    cr_assert(ST_len(I) == 4);
}