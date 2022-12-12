#include <criterion/criterion.h>

#include "../src/parser/operations.h"

Test(testoperations, testgetitems)
{
    Production *prods = productions();
    LR0_Item *items = LR0_items(prods);
    LR0_SymTable st = LR0_symtable();

    LR0_getitems(S_NT_STM, items, st);
    cr_assert(LR0_ST_len(st) == 3);
    cr_assert(LR0_itemeq(st->head->i, items[10]));
    cr_assert(LR0_itemeq(st->head->next->i, items[6]));
    cr_assert(LR0_itemeq(st->head->next->next->i, items[2]));
}