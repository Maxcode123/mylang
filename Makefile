CC=gcc
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
ARGS=-g
TEST=tests

test: test-list test-productions test-items

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

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/parser/%.c
	$(CC) $(ARGS) -c $< -o $@

clean:
	rm -rf obj/* lex/lexer $(SRC)/lex/lex.yy.c $(TEST)/bin/*