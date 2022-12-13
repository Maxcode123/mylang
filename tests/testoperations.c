#include <criterion/criterion.h>

#include "../src/parser/grammar.h"
#include "../src/parser/operations.h"

Test(testoperations, testgetitems)
{
    LR0_SymTable st = LR0_ST_symtable();
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();

    LR0_O_getitems(S_NT_STM, st);
    cr_assert(LR0_ST_len(st) == 3);
    cr_assert(LR0_itemeq(st->head->i, allitems[10]));
    cr_assert(LR0_itemeq(st->head->next->i, allitems[6]));
    cr_assert(LR0_itemeq(st->head->next->next->i, allitems[2]));
}