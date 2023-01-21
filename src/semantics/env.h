#pragma once

#include "../utils/symtable.h"
#include "../parser/ast.h"

typedef SymTable Env; // Environment is a symbol table.

// Global environment.
static Env env;

// Assigns the global environment.
void envinit();

// Returns the global environment.
Env getglobenv();

/* Looks up the given identifier in the global environment and returns the 
value associated with it. If not found prints an error and exits. */
int lookupid(char *id);

// Associates val with id in global environment.
void updtenv(char *id, int val);

// Updates the global environment by evaluating the given statement.
void updtstm(Stm stm);

// Evaluates given expression, updates global environment and returns result.
int evalexp(Exp exprs);

// Evaluates given binop expression and returns result.
int evalbinopexp(Exp binopexp);