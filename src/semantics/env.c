#include "env.h"

void envinit() {
    env = stb_symtable();
}

Env getglobenv() {
    return env;
}

int lookupid(char *id) {
    int *i = malloc(sizeof(*i));
    stb_get(env, id, i);
    if (i == NULL) 
    {
        fprintf(stderr, "Identifier %s used but not defined.\n", id);
        exit(1);
    }
    return *i;
}

void updtenv(char *id, int val) {
    int *i = malloc(sizeof(*i));
    *i = val;
    stb_put(env, node(id, i));
}

void updtstm(Stm stm) {
    switch (stm->kind) {
        case COMPOUND_STM: 
            (updtstm(stm->u.compound.stm1), updtstm(stm->u.compound.stm2));
            break;
        case ASSIGN_STM: 
            updtenv(stm->u.assign.id, evalexp(stm->u.assign.exprs));
            break;
        case PRINT_STM: break;
    }
}

int evalexp(Exp exprs) {
    switch (exprs->kind) {
        case NUM_EXP: return exprs->u.num;
        case OP_EXP: return evalbinopexp(exprs);
        case ESEQ_EXP:
            updtstm(exprs->u.eseq.stmt);
            return evalexp(exprs->u.eseq.exprs);
        case ID_EXP: return lookupid(exprs->u.id);
    }
}

int evalbinopexp(Exp binopexp) {
    switch (binopexp->u.op.oper) {
        case PLUS_BINOP: 
            return evalexp(binopexp->u.op.left) + evalexp(binopexp->u.op.right);
        case MINUS_BINOP:
            return evalexp(binopexp->u.op.left) - evalexp(binopexp->u.op.right);
        case TIMES_BINOP:
            return evalexp(binopexp->u.op.left) * evalexp(binopexp->u.op.right);
        case DIV_BINOP:
            return evalexp(binopexp->u.op.left) / evalexp(binopexp->u.op.right);
    }
}