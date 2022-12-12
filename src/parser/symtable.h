#pragma once

#include "list.h"

typedef struct _LR0_SymTable {
    LR0_ItemNode head;
} *LR0_SymTable;

// Symbol table constructor; allocates memory for the ST and initializes head.
LR0_SymTable LR0_symtable();

/* Points the Item of the given key to i. If there is no such key, points i to
NULL. */
void LR0_ST_get(LR0_SymTable st, key k, LR0_Item *i);

/* Associates Item i with key k. If the key already exists, i overwrites the
current value. */
void LR0_ST_put(LR0_SymTable st, key k, LR0_Item i);
