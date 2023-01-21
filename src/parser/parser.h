#pragma once

#include "adapter.h"
#include "ast.h"
#include "automaton.h"
#include "../utils/stack.h"

typedef Node SymbolNode;    // Node of symbol stack,
typedef Node ASTNode;       // Node of AST stack.
typedef Node StateHashNode; // Node of state stack.

// Grammar symbols stack.
static Stack symbolstk;

// SymbolNode constructor.
SymbolNode symbolnode(symbol s);

// AST nodes stack, used as buffer for AST construction during parsing.
static Stack ASTstk;

// Pops AST stack
AST popASTstk();

// ASTNode constructor. Creates AST node from terminal symbol.
ASTNode astTnode(Token t);

// ASTNode constructor. Creates AST node from non-terminal's symbol and tree.
ASTNode astNTnode(symbol s, void *t);

// State hash stack.
static Stack statestk;

// StateHashNode constructor.
StateHashNode statehnode(key hash);

// Returns current state hash.
key getcsthash();

/* Initializes all productions, items, states, edges and parse table to be used
for parsing. */
void initparse();

// Sets current state to initial state.
void setstinit(StateSet T);

// Parses token array into abstract syntax tree.
void parse(Token *ta);

// Makes changes to stacks and state according to given action.
void apply(Action a, Token t);

// Constructs tree node from given production and tokens, then adds it to the AST.
void astadd(Production p);

// Parses compound statement.
void prscompoundstm();

// Parses assignment statement.
void prsassignstm();

// Parses print statement.
void prsprintstm();

// Parses identifier expression.
void prsidexp();

// Parses numeric expression.
void prsnumexp();

// Parses operation expression.
void prsopexp();

// Parses an expression sequence.
void prseseq();

// Parses pair expression list.
void prspairexplist();

// Parses last expression list.
void prslastexplist();
