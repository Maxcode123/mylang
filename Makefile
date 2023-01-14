CC=gcc
SRC=src
OBJ=obj
PARSERC=$(wildcard $(SRC)/parser/*.c)
PARSERO=$(patsubst $(SRC)/parser/%.c, $(OBJ)/%.o, $(PARSERC))
UTILSC=$(wildcard $(SRC)/utils/*.c)
UTILSO=$(patsubst $(SRC)/utils/%.c, $(OBJ)/%.o, $(UTILSC))
ARGS=-g
TEST=tests
DB=gdb
FILE=test.mylang

debug-file: $(TEST)/bin/main
	clear
	$(DB) --args $< $(FILE)

debug: $(TEST)/bin/main
	clear
	$(DB) $<

run-file: $(TEST)/bin/main
	clear
	$< $(FILE)

run: $(TEST)/bin/main
	clear
	$<

$(TEST)/bin/main: $(TEST)/main.c $(PARSERO) $(UTILSO) $(OBJ)/lex.yy.o 
	$(CC) $^ -o $@

test: test-automaton test-states test-operations test-symtable test-stack test-list test-productions test-items

test-automaton: $(TEST)/bin/automaton
	$<

$(TEST)/bin/automaton: $(TEST)/testautomaton.c $(OBJ)/automaton.o $(OBJ)/states.o $(OBJ)/operations.o $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o $(OBJ)/util.o
	$(CC) $^ -o $@ -lcriterion

test-states: $(TEST)/bin/teststates
	$<

$(TEST)/bin/teststates: $(TEST)/teststates.c $(OBJ)/states.o $(OBJ)/operations.o $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o $(OBJ)/util.o
	$(CC) $^ -o $@ -lcriterion

test-operations: $(TEST)/bin/testoperations
	$<

$(TEST)/bin/testoperations: $(TEST)/testoperations.c $(OBJ)/operations.o $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-symtable: $(TEST)/bin/testsymtable
	$<

$(TEST)/bin/testsymtable: $(TEST)/testsymtable.c $(OBJ)/symtable.o $(OBJ)/list.o $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

test-stack: $(TEST)/bin/teststack
	$<

$(TEST)/bin/teststack: $(TEST)/teststack.c $(OBJ)/stack.o $(OBJ)/list.o
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

test-utils: $(TEST)/bin/testutils
	$<

$(TEST)/bin/testutils: $(TEST)/testutils.c $(OBJ)/util.o
	$(CC) $^ -o $@ -lcriterion

lexer: $(SRC)/scanner/lexer

$(SRC)/scanner/lexer: $(OBJ)/lexdriver.o $(OBJ)/lex.yy.o $(OBJ)/util.o
	$(CC) $(ARGS) $^ -o $@

$(OBJ)/lexdriver.o: $(SRC)/scanner/lexdriver.c
	$(CC) $(ARGS) -c $< -o $@

$(SRC)/scanner/lex.yy.c: $(SRC)/scanner/mylang.lex
	lex -o $@ $<

$(OBJ)/%.o: $(SRC)/utils/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/parser/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/scanner/%.c
	$(CC) $(ARGS) -c $< -o $@

clean:
	rm -rf obj/* src/scanner/lexer src/scanner/lex.yy.c tests/bin/*
