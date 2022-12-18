#pragma once

#include "list.h"

typedef struct _SymTable {
    Node head;
} *SymTable;

// Symbol table constructor; allocates memory for the ST and initializes head.
SymTable ST_symtable();

/* Points the Item of the given key to i. If there is no such key, points i to
NULL. */
void ST_get(SymTable st, key k, void **i);

// Adds a node. If the key already exists returns without doing nothing.
void ST_put(SymTable st, Node in);

// Returns length of symbol table.
int ST_len(SymTable st);

// Clears symbol table.
void ST_clear(SymTable st);

/* Puts the union of st1 and st2 into st1. Inserts all values after given Node.
hashf is used to create hashes for nodes, ieq is used to compare node items. */
void ST_union(
    SymTable st1,
    SymTable st2,
    void (*hashf)(void *, key),
    Node after, bool (*ieq)(void *, void *)
    );

/* Constructs node for symbol table. Allocates memory and creates hash from 
given item. */
Node ST_node(void *i, void (*hashf)(void *, key));

// Prints the the nodes of the symbol table with the given function.
void ST_print(SymTable st, void  (*printfn)(void  *));