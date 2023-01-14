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
    ActionListNode h = lst_list();
    ActionsMapNode an = node(hash, h);
    return an;
}

StateActionsMap *parsetable(StateSet T) {
    StateActionsMap *m = malloc(SYMBOLS*sizeof(StateActionsMap));
    for (int i = 0; i < SYMBOLS; i++) 
    {
        StateActionsMap map = stb_symtable();
        StateNode n = T->head;
        while (n != NULL)
        {
            stb_put(map, mapnode(n->k));
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
    stb_getnode(ptable[X - S_NT_PROGRAM], fromhsh, &m);
    ActionListNode an = node(String(act), action(t, valueh(tohsh)));
    lst_add(an, &(m->i));
}

void reduces(StateSet T) {
    StateNode SN = T->head;
    int p;
    SymbolSet S = stb_symtable();
    while (SN != NULL) // loop on states
    {
        ItemNode in = ((State)(SN->i))->head;
        while (in != NULL) // loop on state items
        {
            if (((LR0_Item)in->i)->before == -1)
            {
                p = prodidx(((LR0_Item)in->i)->p);
                follow(((LR0_Item)in->i)->p->lhs, S);
                addrdc(p, SN->k, S);
            }
            in = in->next;
        }
        SN = SN->next;
    }
    free(S);
}

void addrdc(int p, key hsh, SymbolSet S) {
    if (stb_len(S) == 0) return;
    ActionsMapNode m;
    key k = malloc(sizeof(char)*2);
    // loop through terminal symbols
    for (int i = NON_TERMINALS; i < SYMBOLS; i++)
    {
        symbolhash(&i, k);
        if (!stb_haskey(S, k)) continue;  
        stb_getnode(ptable[i], hsh, &m);
        ActionListNode an = node(String("reduce"), action(REDUCE, valuep(p)));
        lst_add(an, &(m->i));       
    }
    free(k);
}

void symbolhash(symbol *X, key hash) {
    char **s = getsymbols();
    sprintf(hash, "%s", s[*X - S_NT_PROGRAM]);
}

bool symboleq(symbol s1, symbol s2) {
    return s1 == s2;
}

void first(symbol X, SymbolSet S) {
    if (IS_TERMINAL(X))
    {
        int *it = malloc(sizeof(int));
        *it = X;
        stb_put(S, stb_node(it, &symbolhash));
        return;
    }
    Production *p = getprods();
    for (int i = 0 ; i < PRODUCTIONS; i++)
    {
        if (p[i]->lhs == X && IS_TERMINAL(p[i]->rhs[0]))
        {
            int *it = malloc(sizeof(int));
            *it = p[i]->rhs[0];
            stb_put(S, stb_node(it, &symbolhash));
        }
    }
}

void follow(symbol X, SymbolSet S) {
    if (IS_TERMINAL(X)) return;
    Production *p = getprods();
    for (int i = 1; i < PRODUCTIONS; i++) // loop on productions (skip 1st prod)
    {
        for (int j = 0; j < p[i]->len; j++) // loop on production rhs
        {
            if (p[i]->rhs[j] != X) continue;
            SymbolSet S2 = stb_symtable();
            if (j == p[i]->len - 1) // last rhs symbol
            {
                if (p[i]->lhs == X) {free(S2); continue;}
                follow(p[i]->lhs, S2);
            }
            else first(p[i]->rhs[j+1], S2);
            if (stb_len(S2) > 0) stb_union(S, S2, &symbolhash, S->head, &symboleq);
            free(S2);
        }
    }
}