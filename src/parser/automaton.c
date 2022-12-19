#include "automaton.h"

ActionValue valueh(key h) {
    ActionValue v = malloc(sizeof(union _ActionValue));
    v->h = h;
    return v;
}

ActionValue valuep(int p) {
    ActionValue v = malloc(sizeof(union _ActionValue));
    v->p = p;
    return v;
}

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
    key fromhsh, tohsh;
    ActionListNode h; // action list head
    while (n != NULL)
    {
        if (((Edge)n->i)->X < S_NT_PROGRAM + NON_TERMINALS) {n = n->next; continue;}
        fromhsh = malloc(sizeof(char)*50); // from-state hash
        tohsh = malloc(sizeof(char)*50); // to-state hash
        statehash(((Edge)n->i)->from, fromhsh);
        statehash(((Edge)n->i)->to, tohsh);
        ST_get(ptable[((Edge)n->i)->X - S_NT_PROGRAM], fromhsh, &h);
        ActionValue v = valueh(tohsh);
        Action a = action(SHIFT, v);
        ActionListNode an = node(String("shift"), a);
        add(an, &h);
        n = n->next;
    }
}
