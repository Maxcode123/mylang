#pragma once

#include "states.h"

typedef enum Actype {SHIFT, GOTO, REDUCE, ACCEPT, REJECT};

typedef struct _Action {
    enum Actype type;
    union val {key h; int p;}; // key hash for shift and goto, int production for reduce    
} *Action;

typedef Node ActionsMapNode; // Node of map, contains list actions list.
typedef Node ActionListNode; // Node of actions list.

typedef SymTable StateActionsMap; // Mapping of state hash to Actions

static StateActionsMap *ptable; // parse table, indeces correspond to symbol-10

static key sthash; // hash of current state

// ActionsMapNode constructor. Allocates memory for list and map node.
ActionsMapNode mapnode();

// Allocates memory and returns parse table.
StateActionsMap *parsetable(StateSet T);

// Assigns parse table.
void initptable();

// Populates shift actions in parse table.
void shifts(EdgeSet E);

// Populates goto actions in parse table.
void gotos(EdgeSet E);

// Populates reduce actions in parse table.
void reduces(StateSet T);
