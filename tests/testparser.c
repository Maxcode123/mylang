#include <criterion/criterion.h>

#include "../src/parser/parser.h"

Test(testparser, testparse1)
{
    // a = 155
    Token *ta = malloc(sizeof(Token)*4);
    ta[0] = (yylval.sval = String("a"), incrtklen(), token(ID));
    ta[1] = (incrtklen(), token(ASSIGN));
    ta[2] = (yylval.ival = 155, incrtklen(), token(NUM));
    ta[3] = (incrtklen(), token(-1));
    parse(ta);
    Stm ast = (Stm)popASTstk();
    cr_assert(ast->kind == ASSIGN_STM);
    cr_assert(strcmp(ast->u.assign.id, "a") == 0);
    cr_assert(ast->u.assign.exprs->kind == NUM_EXP);
    cr_assert(ast->u.assign.exprs->u.num == 155);
}

Test(testparser, testparse2)
{
    // myvar = 123; mtp = (c = myvar, c + 2)
    Token *ta = malloc(sizeof(Token)*16);
    ta[0] = (yylval.sval = String("myvar"), incrtklen(), token(ID));
    ta[1] = (incrtklen(), token(ASSIGN));
    ta[2] = (yylval.ival = 123, incrtklen(), token(NUM));
    ta[3] = (incrtklen(), token(SEMICOLON));
    ta[4] = (yylval.sval = String("mtp"), incrtklen(), token(ID));
    ta[5] = (incrtklen(), token(ASSIGN));
    ta[6] = (incrtklen(), token(LPAREN));
    ta[7] = (yylval.sval = String("c"), incrtklen(), token(ID));
    ta[8] = (incrtklen(), token(ASSIGN));
    ta[9] = (yylval.sval = String("myvar"), incrtklen(), token(ID));
    ta[10] = (incrtklen(), token(COMMA));
    ta[11] = (yylval.sval = String("c"), incrtklen(), token(ID));
    ta[12] = (incrtklen(), token(PLUS));
    ta[13] = (yylval.ival = 2, incrtklen(), token(NUM));
    ta[14] = (incrtklen(), token(RPAREN));
    ta[15] = (incrtklen(), token(-1));
    parse(ta);
    Stm ast = (Stm)popASTstk();
    cr_assert(ast->kind == COMPOUND_STM);
    cr_assert(ast->u.compound.stm1->kind == ASSIGN_STM);
    cr_assert(strcmp(ast->u.compound.stm1->u.assign.id, "myvar") == 0);
    cr_assert(ast->u.compound.stm1->u.assign.exprs->kind == NUM_EXP);
    cr_assert(ast->u.compound.stm1->u.assign.exprs->u.num == 123);
    cr_assert(ast->u.compound.stm2->kind == ASSIGN_STM);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->kind == ESEQ_EXP);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.stmt->kind == ASSIGN_STM);
    cr_assert(strcmp(ast->u.compound.stm2->u.assign.exprs->u.eseq.stmt->u.assign.id, "c") == 0);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.stmt->u.assign.exprs->kind == ID_EXP);
    cr_assert(strcmp(ast->u.compound.stm2->u.assign.exprs->u.eseq.stmt->u.assign.exprs->u.id, "myvar") == 0);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->kind == OP_EXP);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->u.op.left->kind == ID_EXP);
    cr_assert(strcmp(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->u.op.left->u.id, "c") == 0);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->u.op.oper == PLUS_BINOP);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->u.op.right->kind == NUM_EXP);
    cr_assert(ast->u.compound.stm2->u.assign.exprs->u.eseq.exprs->u.op.right->u.num == 2);
}