#include "automaton.h"

void printaction(Action a) {
    switch (a->type) {
        case SHIFT: printf("shift %s", a->val->h); break;
        case GOTO: printf("goto %s", a->val->h); break;
        case REDUCE: printf("reduce %d", a->val->p); break;
        case ACCEPT: printf("accept"); break;
        case REJECT: printf("reject"); break;
    }
    printf("\n");
    return;
}

void printactlst(ActionListNode h) {
    ActionListNode n = h;
    while (n != NULL)
    {
        printaction((Action)n->i);
        n = n->next;
    }
}

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

StateActionsMap *getptable() {
    return ptable;
}

void shiftgoto(EdgeSet E) {
    EdgeNode n = E->head;
    key fromhsh, tohsh;
    enum Actype t;
    while (n != NULL)
    {
        fromhsh = malloc(sizeof(char)*50); // from-state hash
        tohsh = malloc(sizeof(char)*50); // to-state hash
        statehash(((Edge)n->i)->from, fromhsh);
        statehash(((Edge)n->i)->to, tohsh);
        if (((Edge)n->i)->X < S_NT_PROGRAM + NON_TERMINALS) 
        {

            n = n->next; continue;
        }
        t = SHIFT;
        addact(((Edge)n->i)->X, fromhsh, tohsh, t);
        n = n->next;
    }
}

void addact(symbol X, key fromhsh, key tohsh, enum Actype t) {
    ActionsMapNode m;
    ST_getnode(ptable[X - S_NT_PROGRAM], fromhsh, &m);
    ActionListNode an = node(String("shift"), action(t, valueh(tohsh)));
    add(an, &(m->i));
}

void addgt(symbol X, key fromhsh, key tohsh) {
    ActionsMapNode m;
    ST_getnode(ptable[X - S_NT_PROGRAM], fromhsh, &m);
    ActionListNode an = node(String("shift"), action(GOTO, valueh(tohsh)));
    add(an, &(m->i));
}