CC=gcc
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
ARGS=-g
TEST=tests

test-productions: $(TEST)/bin/testproductions
	$<

$(TEST)/bin/testproductions: $(TEST)/testproductions.c $(OBJ)/grammar.o
	$(CC) $^ -o $@ -lcriterion

lexer: $(OBJ)/lexdriver.o $(OBJ)/lex.yy.o $(OBJ)/util.o
	$(CC) $(ARGS) $^ -o $@

$(SRC)/lex.yy.c: $(SRC)/mylang.lex
	lex -o $@ $< 

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(ARGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/parser/%.c
	$(CC) $(ARGS) -c $< -o $@

clean:
	rm -rf obj/* lexer $(SRC)/lex.yy.c $(TEST)/bin/*