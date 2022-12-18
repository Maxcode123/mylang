#include "automaton.h"


ActionsMapNode mapnode() {
    ActionListNode h = list();
    ActionsMapNode an = node("", h);
    return an;
}


StateActionsMap *parsetable(StateSet T) {
    StateActionsMap t = malloc(SYMBOLS*sizeof(StateActionsMap));
    for (int i = 0; i < SYMBOLS; i++) 
    {
        StateActionsMap map = ST_symtable();
        StateNode n = T->head;
        while (n != NULL)
        {
            ST_put(map, mapnode());
            n = n->next;
        }
    }
}