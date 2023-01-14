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
            int *i = malloc(sizeof(*i));
            *i = t->ival;
            return node(k, i);
        case S_T_PLUS:
            enum Binop *i = malloc(sizeof(*i));
            *i = PLUS_BINOP;
            return node(k, i);
        case S_T_MINUS:
            enum Binop *i = malloc(sizeof(*i));
            *i = MINUS_BINOP;
            return node(k, i);
        case S_T_TIMES:
            enum Binop *i = malloc(sizeof(*i));
            *i = TIMES_BINOP;
            return node(k, i);
        case S_T_DIV:
            enum Binop *i = malloc(sizeof(*i));
            *i = DIV_BINOP;
            return node(k, i);
        case S_T_ID:
            char *i = malloc(sizeof(*i)*50);
            strcpy(i, (char*)&t->sval);
            return node(k, i);
    }
}

void initparse() {
    LR0_inititems();
    StateSet T = stb_symtable();
    EdgeSet E = stb_symtable();

    states(T, E);
    initptable(T);
    shiftgoto(E);
    reduces(T);
}

AST parse(Token *ta) {
    initparse();
    StateActionsMap *pt = getptable();
    int i, len = gettklen();
    Token t;
    for (i = 0; i < len; i++)
    {
        t = ta[i];
        ActionListNode h;
        stb_get(ptable[t->s - S_NT_PROGRAM], csthash, &h);
        Action a = h->i;
        apply(a, t);
    }
    if ((symbol)stk_pop(&symbolstk)->i == S_NT_STM) return;
    fprintf(stderr, "Stm not found in symbol stack after parsing.\n");
    exit(EXIT_FAILURE);
}

void apply(Action a, Token t) {
    if (a->type == SHIFT)
    {
        stk_push(symbolnode(t->s), &symbolstk);
        csthash = a->val->h;
        if (!IS_SEMANTIC(t->s)) return;
        stk_push(astTnode(t), &ASTstk);
    }
    else if (a->type == REDUCE)
    {
        StateActionsMap *pt = getptable();
        Production p = getprods()[a->val->p];
        for (int j = 0; j < p->len; j++) stk_pop(&symbolstk);
        stk_push(symbolnode(p->lhs), &symbolstk);
        astadd(p);
        ActionListNode h;
        stb_get(ptable[p->lhs - S_NT_PROGRAM], csthash, &h);
        Action gta = h->i; // goto action
        if (gta->type != GOTO)
        {
            fprintf(stderr, "GOTO action expected.\n");
            exit(EXIT_FAILURE);
        }
        csthash = gta->val->h;
    }
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

void prslastexplit() {
    ExpList expl = lastexplist((Exp)stk_pop(&ASTstk)->i);
    stk_push(astNTnode(S_NT_EXPLIST, expl), &ASTstk);
}
