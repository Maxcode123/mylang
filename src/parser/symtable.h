#pragma once

#include "list.h"

typedef struct _LR0_SymTable {
    LR0_ItemNode head;
} *LR0_SymTable;

// Symbol table constructor; allocates memory for the ST and initializes head.
LR0_SymTable LR0_ST_symtable();

/* Points the Item of the given key to i. If there is no such key, points i to
NULL. */
void LR0_ST_get(LR0_SymTable st, key k, LR0_Item *i);

// Adds a node. If the key already exists returns without doing nothing.
void LR0_ST_put(LR0_SymTable st, LR0_ItemNode in);

// Returns length of symbol table.
int LR0_ST_len(LR0_SymTable st);

/* Constructs node for symbol table. Allocates memory and creates hash from 
given item. */
LR0_ItemNode LR0_ST_node(LR0_Item i);

// Clears symbol table.
void LR0_ST_clear(LR0_SymTable st);

// Puts the union of st1 and st2 into st1. Inserts all values after head.
void LR0_ST_union(LR0_SymTable st1, LR0_SymTable st2);