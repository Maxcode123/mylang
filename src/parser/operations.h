#pragma once

#include "symtable.h"

// Calculates the closure of I and inserts it into I.
void LR0_closure(LR0_SymTable I);

/* Inserts into st all Items where the left hand side of the production is
X and the right hand side starts with dot (X->•γ). */
void LR0_getitems(symbol X, LR0_Item *allitems, LR0_SymTable st);

// Calculates the GOTO set for set I and item X and inserts it into G.
void LR0_goto(LR0_SymTable I, LR0_Item X, LR0_SymTable G);
