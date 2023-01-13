#pragma once

typedef struct _Stm *Stm;
typedef struct _Exp *Exp;
typedef struct _ExpList *ExpList;

enum Binop {PLUS_BINOP, MINUS_BINOP, TIMES_BINOP, DIV_BINOP};
enum StmType {COMPOUND_STM, ASSIGN_STM, PRINT_STM};
enum ExpType {ID_EXP, NUM_EXP, OP_EXP, ESEQ_EXP};
enum ExpListType {PAIR_EXPLIST, LAST_EXPLIST};


// statement
typedef struct _Stm {
    enum StmType kind;
    union {
        struct {Stm stm1, stm2;} compound;
        struct {char *id; Exp exprs;} assign;
        struct {ExpList exps;} print;
    } u;
} *Stm;

// statement constructors
Stm compoundstm(Stm stm1, Stm stm2);
Stm assignstm(char *id, Exp exprs);
Stm printstm(ExpList exps);

// expression
typedef struct _Exp {
    enum ExpType kind;
    union {
        char *id;
        int num;
        struct {Exp left; enum Binop oper; Exp right;} op;
        struct {Stm stmt; Exp exprs;} eseq;
    } u;
} *Exp;

// expression constructors
Exp idexp(char *id);
Exp numexp(int num);
Exp opexp(Exp left, enum Binop oper, Exp right);
Exp eseq(Stm stm, Exp exprs);

// expression list
typedef struct _ExpList {
    enum ExpListType kind;
    union {
        struct {Exp head; ExpList tail;} pair;
        Exp last;
    } u;
} *ExpList;

// expression list constructors
ExpList pairexplist(Exp head, ExpList tail);
ExpList lastexplist(Exp last);