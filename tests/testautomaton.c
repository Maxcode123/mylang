#include <criterion/criterion.h>

#include "../src/parser/automaton.h"

Test(testautomaton, testactioninit)
{
    ActionValue v = { .h = "key" };
    Action a1 = action(SHIFT, v);
    cr_assert(a1->type == SHIFT);
    cr_assert(strcmp(a1->val.h, "key") == 0);

    ActionValue v2 = { .p = 2};
    Action a2 = action(REDUCE, v2);
    cr_assert(a2->type == REDUCE);
    cr_assert(a2->val.p == 2);
}

Test(testautomaton, testmapnodeinit)
{
    ActionsMapNode n = mapnode("hash");
    cr_assert(strcmp(n->k, "hash") == 0);    
    cr_assert(n->i == NULL);
}

Test(testautomaton, testparsetable)
{
    LR0_inititems();
    StateSet T = ST_symtable();
    EdgeSet E = ST_symtable();
    states(T, E);
    StateActionsMap *m = parsetable(T);
    for (int i = 0; i < SYMBOLS; i++)
    {
        cr_assert(ST_len(m[i]) == ST_len(T));                
    }
}