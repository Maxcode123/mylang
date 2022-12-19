#include "automaton.h"

Action action(enum Actype t, ActionValue v) {
    Action a = malloc(sizeof(struct _Action));
    a->type = t;
    a->val = v;
    return a;
}

ActionsMapNode mapnode(key hash) {
    ActionListNode h = list();
    ActionsMapNode an = node(hash, h);
    return an;
}

StateActionsMap *parsetable(StateSet T) {
    StateActionsMap *m = malloc(SYMBOLS*sizeof(StateActionsMap));
    for (int i = 0; i < SYMBOLS; i++) 
    {
        StateActionsMap map = ST_symtable();
        StateNode n = T->head;
        while (n != NULL)
        {
            ST_put(map, mapnode(n->k));
            n = n->next;
        }
        m[i] = map;
    }
    return m;
}

void initptable(StateSet T) {
    ptable = parsetable(T);
}

void shifts(EdgeSet E) {
    EdgeNode n = E->head;
    key buff = malloc(sizeof(char)*50);
    ActionListNode h;
    while (n != NULL)
    {
        if (((Edge)n->i)->X < S_NT_PROGRAM + NON_TERMINALS) {n = n->next; continue;}
        statehash(((Edge)n->i)->from, buff);
        ST_get(ptable[((Edge)n->i)->X - S_NT_PROGRAM], buff, h);

    }
}
