CC=gcc
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
ARGS=-g
TEST=tests
DB=gdb

debug: $(TEST)/bin/main
	$(DB) $<

$(TEST)/bin/main: $(TEST)/main.c $(OBJ)/operations.o $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@

test: test-operations test-symtable test-list test-productions test-items

test-operations: $(TEST)/bin/testoperations
	$<

$(TEST)/bin/testoperations: $(TEST)/testoperations.c $(OBJ)/operations.o $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-symtable: $(TEST)/bin/testsymtable
	$<

$(TEST)/bin/testsymtable: $(TEST)/testsymtable.c $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-list: $(TEST)/bin/testlist
	$<

$(TEST)/bin/testlist: $(TEST)/testlist.c $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-productions: $(TEST)/bin/testproductions
	$<

$(TEST)/bin/testproductions: $(TEST)/testproductions.c $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-items: $(TEST)/bin/testitems
	$<

$(TEST)/bin/testitems: $(TEST)/testitems.c $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

lex/lexer: $(OBJ)/lexdriver.o $(OBJ)/lex.yy.o $(OBJ)/util.o
	$(CC) $(ARGS) $^ -o $@

$(SRC)/lex/lex.yy.c: $(SRC)/lex/mylang.lex
	lex -o $@ $<

$(OBJ)/%.o: $(SRC)/utils/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/parser/%.c
	$(CC) $(ARGS) -c $< -o $@

clean:
	rm -rf obj/* lex/lexer $(SRC)/lex/lex.yy.c $(TEST)/bin/*
