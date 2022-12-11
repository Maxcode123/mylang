#pragma once

#include "list.h"

typedef struct _SymTable {
    ItemNode head;
} *SymTable;

// Symbol table constructor; allocates memory for the ST and initializes head.
SymTable symtable();

/* Points the Item of the given key to i. If there is no such key, points i to 
NULL. */
void get(SymTable st, key k, Item i);

/* Associates Item i with key k. If the key already exists, i overwrites the 
current value. */
void put(SymTable st, key k, Item i);
