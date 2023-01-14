#pragma once

#include "list.h"

typedef struct _SymTable {
    Node head;
} *SymTable;

typedef ListItem SymTableItem;

// Symbol table constructor; allocates memory for the ST and initializes head.
SymTable stb_symtable();

// Points i to item with key k.
void stb_get(SymTable st, key k, SymTableItem *i);

// Points in to the node with key k.
void stb_getnode(SymTable st, key k, Node *in);

// Returns true if there is a node in st with key k.
bool stb_haskey(SymTable st, key k);

// Adds a node. If the key already exists returns without doing nothing.
void stb_put(SymTable st, Node in);

// Returns length of symbol table.
int stb_len(SymTable st);

// Clears symbol table.
void stb_clear(SymTable st);

/* Puts the union of st1 and st2 into st1. Inserts all values after given Node.
hashf is used to create hashes for nodes, ieq is used to compare node items. */
void stb_union(
    SymTable st1,
    SymTable st2,
    void (*hashf)(SymTableItem, key),
    Node after, bool (*ieq)(SymTableItem, SymTableItem)
    );

/* Constructs node for symbol table. Allocates memory and creates hash from 
given item. */
Node stb_node(SymTableItem i, void (*hashf)(SymTableItem, key));

// Prints the items of the nodes of the symbol table with the given function.
void stb_print(SymTable st, void (*printfn)(SymTableItem));

// Prints the keys of the symbol table.
void stb_printk(SymTable st);

// Prints the keys and items of the symbol table.
void stb_printn(SymTable st, void (*printfn)(SymTableItem));