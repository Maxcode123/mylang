#pragma once

#include "list.h"

typedef struct _SymTable {
    void *head;
} *SymTable;

// Symbol table constructor; allocates memory for the ST and initializes head.
SymTable ST_symtable();

/* Points the Item of the given key to i. If there is no such key, points i to
NULL. */
void ST_get(SymTable st, key k, LR0_Item *i);

// Adds a node. If the key already exists returns without doing nothing.
void ST_put(SymTable st, Node in);

// Returns length of symbol table.
int ST_len(SymTable st);

/* Constructs node for symbol table. Allocates memory and creates hash from 
given item. */
Node ST_node(LR0_Item i);

// Clears symbol table.
void ST_clear(SymTable st);

// Puts the union of st1 and st2 into st1. Inserts all values after head.
void ST_union(SymTable st1, SymTable st2);