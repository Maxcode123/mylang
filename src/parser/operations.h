#pragma once

#include "grammar.h"
#include "../utils/symtable.h"

typedef SymTable ItemSet;

// Calculates the closure of I and inserts it into I.
void LR0_closure(ItemSet I);

/* Inserts into st all items where the left hand side of the production is
X and the right hand side starts with dot (X->•γ). If there exists a production
X->Y where Y is non-terminal, also puts into st all Y->•γ items.*/
void LR0_getitems(symbol X, ItemSet st);

// Calculates the GOTO set for set I and item X and inserts it into G.
void LR0_goto(ItemSet I, symbol X, ItemSet G);

