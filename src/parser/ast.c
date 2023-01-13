#include "ast.h"

Stm compoundstm(Stm stm1, Stm stm2) {
    Stm s = malloc(sizeof(*s));
    s->kind = COMPOUND_STM;
    s->u.compound.stm1 = stm1;
    s->u.compound.stm2 = stm2;
    return s;
}

Stm assignstm(char *id, Exp exprs) {
    Stm s = malloc(sizeof(*s));
    s->kind = ASSIGN_STM;
    s->u.assign.id = id;
    s->u.assign.exprs = exprs;
    return s;
}

Stm printstm(ExpList exps) {
    Stm s = malloc(sizeof(*s));
    s->kind = PRINT_STM;
    s->u.print.exps = exps;
}

Exp idexp(char *id) {
    Exp e = malloc(sizeof(*e));
    e->kind = ID_EXP;
    e->u.id = id;
    return e;
}

Exp numexp(int num) {
    Exp e = malloc(sizeof(*e));
    e->kind = NUM_EXP;
    e->u.num = num;
    return e;
}

Exp opexp(Exp left, Binop oper, Exp right) {
    Exp e = malloc(sizeof(*e));
    e->kind = OP_EXP;
    e->u.op.left = left;
    e->u.op.oper = oper;
    e->u.op.right = right;
    return e;
}

Exp eseq(Stm stm, Exp exprs) {
    Exp e = malloc(sizeof(*e));
    e->kind = ESEQ_EXP;
    e->u.eseq.stmt = stm;
    e->u.eseq.exprs = exprs;
    return e;
}

ExpList pairexplist(Exp head, ExpList tail) {
    ExpList el = malloc(sizeof(*el));
    el->kind = PAIR_EXPLIST;
    el->u.pair.head = head;
    el->u.pair.tail = tail;
    return el;
}

ExpList lastexplist(Exp last) {
    ExpList el = malloc(sizeof(*el));
    el->kind = LAST_EXPLIST;\
    el->u.last = last;
    return el;
}