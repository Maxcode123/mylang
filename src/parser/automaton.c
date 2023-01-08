#include "automaton.h"

void printaction(Action a) {
    switch (a->type) {
        case SHIFT: printf("shift %s", a->val->h); break;
        case GOTO: printf("goto %s", a->val->h); break;
        case REDUCE: printf("reduce %d", a->val->p); break;
        case ACCEPT: printf("accept"); break;
        case REJECT: printf("reject"); break;
    }
    printf("  ");
    return;
}

void printactlst(ActionListNode h) {
    ActionListNode n = h;
    if (n == NULL) {printf("\n"); return;}
    while (n != NULL)
    {
        printaction((Action)n->i);
        n = n->next;
    }
    printf("\n");
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
        if (((Edge)n->i)->X < S_NT_PROGRAM + NON_TERMINALS) t = GOTO;
        else t = SHIFT;
        addact(((Edge)n->i)->X, fromhsh, tohsh, t);
        n = n->next;
    }
}

void addact(symbol X, key fromhsh, key tohsh, enum Actype t) {
    ActionsMapNode m;
    key act = "shift";
    if (t == GOTO) act = "goto";
    ST_getnode(ptable[X - S_NT_PROGRAM], fromhsh, &m);
    ActionListNode an = node(String(act), action(t, valueh(tohsh)));
    add(an, &(m->i));
}

void reduces(StateSet T) {
    StateNode SN = T->head;
    int p;
    while (SN != NULL) // loop on states
    {
        ItemNode in = ((State)(SN->i))->head;
        while (in != NULL) // loop on state items
        {
            if (((LR0_Item)in->i)->before == -1)
            {
                p = prodidx(((LR0_Item)in->i)->p);
                addrdc(p, SN->k);
            }
            in = in->next;
        }
        SN = SN->next;
    }
}

void addrdc(int p, key hsh) {
    ActionsMapNode m;
    // loop through terminal symbols
    for (int i = NON_TERMINALS; i < SYMBOLS; i++)
    {
        ST_getnode(ptable[i], hsh, &m);
        ActionListNode an = node(String("reduce"), action(REDUCE, valuep(p)));
        add(an, &(m->i));       
    }
}