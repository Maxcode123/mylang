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
    // if symbol is num or binop, semantic value is integer or enum int value, respectively.
    if (t->s == S_T_NUM || t->s == S_T_PLUS || t->s == S_T_MINUS || t->s == S_T_TIMES || t->s == S_T_DIV) 
    {
        int *j = malloc(sizeof(*j));
        *j = t->ival;
        return node(k, j);
    }
    // if symbol is id, semantic value is id's string value.
    else if (t->s == S_T_ID) 
    {
        char *c = malloc(sizeof(*c)*50);
        strcpy(c, (char*)&t->sval);
        return node(k, c);
    }
}

void initparse() {
    LR0_inititems();
    StateSet T = ST_symtable();
    EdgeSet E = ST_symtable();

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
        ST_get(ptable[t->s - S_NT_PROGRAM], csthash, &h);
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
        ST_get(ptable[p->lhs - S_NT_PROGRAM], csthash, &h);
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
        case 1:
        case 2:
        case 3:
        // Exp
        case 4:
        case 5:
        case 6:
        case 7:
        // ExpList
        case 8:
        case 9:
        // BinOp
        case 10:
        case 11:
        case 12:
        case 13:
    }    
}