#include "parser.h"

SymbolNode symbolnode(symbol s) {
    key k = malloc(sizeof(*k)*10);
    symbol *i = malloc(sizeof(*i));
    *i = s;
    strcpy(k, getsymbols()[s-S_NT_PROGRAM]);
    SymbolNode sn = node(k, i);
    return sn;
}

ASTNode astTnode(Token t) {
    key k = malloc(sizeof(*k)*10);
    strcpy(k, getsymbols()[t->s-S_NT_PROGRAM]);
    switch (t->s) {
        case S_T_NUM:
            int *n = malloc(sizeof(*n));
            *n = t->ival;
            return node(k, n);
        case S_T_PLUS:
            enum Binop *p = malloc(sizeof(*p));
            *p = PLUS_BINOP;
            return node(k, p);
        case S_T_MINUS:
            enum Binop *m = malloc(sizeof(*m));
            *m = MINUS_BINOP;
            return node(k, m);
        case S_T_TIMES:
            enum Binop *ti = malloc(sizeof(*ti));
            *ti = TIMES_BINOP;
            return node(k, ti);
        case S_T_DIV:
            enum Binop *d = malloc(sizeof(*d));
            *d = DIV_BINOP;
            return node(k, d);
        case S_T_ID:
            char *i = malloc(sizeof(*i)*50);
            strcpy(i, (char*)&t->sval);
            return node(k, i);
    }
}

ASTNode astNTnode(symbol s, void *t) {
    key k = malloc(sizeof(*k)*10);
    strcpy(k, getsymbols()[s-S_NT_PROGRAM]);
    return node(k, t);    
}

StateHashNode statehnode(key hash) {
    key k = malloc(sizeof(*k)*50);
    strcpy(k, hash);
    return node(k, NULL);
}

key getcsthash() {
    return statestk->k;
}

void initparse() {
    LR0_inititems();
    StateSet T = stb_symtable();
    EdgeSet E = stb_symtable();

    states(T, E);
    initptable(T);
    shiftgoto(E);
    accept(T);
    reduces(T);
    setstinit(T);
}

void setstinit(StateSet T) {
    LR0_Item *items = LR0_getallitems();
    StateNode SN = T->head;
    while (SN != NULL) // loop on states
    {
        ItemNode in = ((State)(SN->i))->head;
        while (in != NULL) // loop on state items
        {
            if (LR0_itemeq((LR0_Item)in->i, items[0]))
            {
                stk_push(statehnode(SN->k), &statestk);
                return;
            }
            in = in->next;
        }
        SN = SN->next;
    }
}

AST parse(Token *ta) {
    initparse();
    StateActionsMap *pt = getptable();
    int i, len = gettklen();
    Token t;
    char **symbols = getsymbols();
    for (i = 0; i < len; i++)
    {
        t = ta[i];
        stk_printk(symbolstk);
        printf(" in state: %s, next token: %s\n", getcsthash(), symbols[t->s-S_NT_PROGRAM]);
        ActionListNode h;
        stb_get(pt[t->s - S_NT_PROGRAM], getcsthash(), &h);
        Action a = h->i;
        apply(a, t);
        if (a->type == REDUCE) i--; // Token is not consumed from reduce action.
        else if (a->type == ACCEPT) 
        {
            printf("SYNTAX CORRECT.\n");
            return;
        }
    }
}

void apply(Action a, Token t) {
    if (a->type == SHIFT)
    {
        stk_push(symbolnode(t->s), &symbolstk);
        stk_push(statehnode(a->val->h), &statestk);
        if (!IS_SEMANTIC(t->s)) return;
        stk_push(astTnode(t), &ASTstk);
    }
    else if (a->type == REDUCE)
    {
        StateActionsMap *pt = getptable();
        Production p = getprods()[a->val->p];
        key sthash;
        for (int j = 0; j < p->len; j++) 
        {
            free(stk_pop(&symbolstk));
            free(stk_pop(&statestk));
        }
        stk_push(symbolnode(p->lhs), &symbolstk);
        astadd(p);
        ActionListNode h;
        stb_get(pt[p->lhs - S_NT_PROGRAM], getcsthash(), &h);
        Action gta = h->i; // goto action
        if (gta->type != GOTO)
        {
            fprintf(stderr, "GOTO action expected.\n");
            exit(EXIT_FAILURE);
        }
        stk_push(statehnode(gta->val->h), &statestk);
    }
    else if (a->type == ACCEPT) return;
}

void astadd(Production p) {
    int i = prodidx(p);
    if (i == PRODUCTION_NOT_FOUND) 
    {
        fprintf(stderr, "Production not found.\n");
        exit(EXIT_FAILURE);    
    }
    switch (i) {
        // Stm
        case 1: prscompoundstm(); break;
        case 2: prsassignstm(); break;
        case 3: prsprintstm(); break;
        // Exp
        case 4: prsidexp(); break;
        case 5: prsnumexp(); break;
        case 6: prsopexp(); break;
        case 7: prseseq(); break;
        // ExpList
        case 8: prspairexplist(); break;
        case 9: prslastexplist(); break;
    }
}

void prscompoundstm() {
    Stm right = (Stm)stk_pop(&ASTstk)->i;
    Stm stm = compoundstm((Stm)stk_pop(&ASTstk)->i, right);
    stk_push(astNTnode(S_NT_STM, stm), &ASTstk);
}

void prsassignstm() {
    Exp exprs = (Exp)stk_pop(&ASTstk)->i;
    Stm stm = assignstm(*(char**)stk_pop(&ASTstk)->i, exprs);
    stk_push(astNTnode(S_NT_STM, stm), &ASTstk);
}

void prsprintstm() {
    Stm stm = printstm((ExpList)stk_pop(&ASTstk)->i);
    stk_push(astNTnode(S_NT_STM, stm), &ASTstk);
}

void prsidexp() {
    Exp exprs = idexp(*(char**)stk_pop(&ASTstk)->i);
    stk_push(astNTnode(S_NT_EXP, exprs), &ASTstk);
}

void prsnumexp() {
    Exp exprs = numexp(*(int*)stk_pop(&ASTstk)->i);
    stk_push(astNTnode(S_NT_EXP, exprs), &ASTstk);
}

void prsopexp() {
    Exp right = (Exp)stk_pop(&ASTstk)->i;
    enum Binop op = *(enum Binop*)stk_pop(&ASTstk)->i;
    Exp exprs = opexp((Exp)stk_pop(&ASTstk)->i, op, right);
    stk_push(astNTnode(S_NT_EXP, exprs), &ASTstk);
}

void prseseq() {
    Exp exprs = (Exp)stk_pop(&ASTstk)->i;
    Exp e = eseq((Stm)stk_pop(&ASTstk)->i, exprs);
    stk_push(astNTnode(S_NT_EXP, e), &ASTstk);
}

void prspairexplist() {
    ExpList tail = (ExpList)stk_pop(&ASTstk)->i;
    ExpList expl = pairexplist((Exp)stk_pop(&ASTstk)->i, tail);
    stk_push(astNTnode(S_NT_EXPLIST, expl), &ASTstk);
}

void prslastexplist() {
    ExpList expl = lastexplist((Exp)stk_pop(&ASTstk)->i);
    stk_push(astNTnode(S_NT_EXPLIST, expl), &ASTstk);
}
