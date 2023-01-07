#pragma once

#include "list.h"

typedef struct _SymTable {
    Node head;
} *SymTable;

typedef ListItem SymTableItem;

// Symbol table constructor; allocates memory for the ST and initializes head.
SymTable ST_symtable();

// Points i to item with key k.
void ST_get(SymTable st, key k, SymTableItem *i);

// Returns true if there is a node in st with key k.
bool ST_haskey(SymTable st, key k);

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
    void (*hashf)(SymTableItem, key),
    Node after, bool (*ieq)(SymTableItem, SymTableItem)
    );

/* Constructs node for symbol table. Allocates memory and creates hash from 
given item. */
Node ST_node(SymTableItem i, void (*hashf)(SymTableItem, key));

// Prints the nodes of the symbol table with the given function.
void ST_print(SymTable st, void  (*printfn)(SymTableItem));