#pragma once

#include "states.h"

typedef enum Actype {SHIFT, GOTO, REDUCE, ACCEPT, REJECT};

typedef union _ActionValue {
    key h; // hash for shit and goto actions
    int p; // production number for reduce actions
} *ActionValue;

typedef struct _Action {
    enum Actype type;
    ActionValue val;     
} *Action;

typedef Node ActionsMapNode; // Node of map, contains list actions list.
typedef Node ActionListNode; // Node of actions list.

typedef SymTable StateActionsMap; // Mapping of state hash to Actions

static StateActionsMap *ptable; // parse table, indeces correspond to symbol-10

static key sthash; // hash of current state

// ActionValue constructor, allocates memory for ActionValue.
ActionValue valueh(key h);

// ActionValue constructor, allocates memory for ActionValue.
ActionValue valuep(int p);

// Action constructor, allocates memory for Action.
Action action(enum Actype t, ActionValue v);

// ActionsMapNode constructor, allocates memory for list and map node.
ActionsMapNode mapnode(key hash);

// Allocates memory and returns parse table.
StateActionsMap *parsetable(StateSet T);

// Assigns parse table.
void initptable(StateSet T);

// Populates shift actions in parse table.
void shifts(EdgeSet E);

// Populates goto actions in parse table.
void gotos(EdgeSet E);

// Populates reduce actions in parse table.
void reduces(StateSet T);
