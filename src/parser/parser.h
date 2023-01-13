#pragma once

#include "adapter.h"
#include "ast.h"
#include "../utils/stack.h"

// State stack.
static Stack statestk;

// Symbol stack.
static Stack symbolstk;

// AST nodes stack, used as buffer for AST construction during parsing.
static Stack ASTstk;

// Parses token array into abstract syntax tree.
AST parse(Token *t);
