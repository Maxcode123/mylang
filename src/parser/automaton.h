#pragma once

#include "states.h"

typedef enum Actype {SHIFT, GOTO, REDUCE, ACCEPT, REJECT};

typedef union _ActionValue {
    key h; // hash for shift and goto actions
    int p; // production number for reduce actions
} *ActionValue;

typedef struct _Action {
    enum Actype type;
    ActionValue val;     
} *Action;

typedef Node ActionsMapNode; // Node of map, contains list actions list.
typedef Node ActionListNode; // Node of actions list.

typedef SymTable StateActionsMap; // Mapping of state hash to Actions

/* parse table, indeces correspond to {symbol}-10. Each item is a symbol table 
(StateActionsMap) where state hashes are keys and lists of Actions are items.*/
static StateActionsMap *ptable;

static key sthash; // hash of current state

// Prints Action in nice format.
void printaction(Action a);

// Prints action list in nice format.
void printactlst(ActionListNode h);

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

// Fetches parse table.
StateActionsMap *getptable();

// Populates shift and goto actions in parse table.
void shiftgoto(EdgeSet E);

// Adds a shift or goto action from state with hash fromhsh to state with hash tohsh.
void addact(symbol X, key fromhsh, key tohsh, enum Actype t);

// Populates reduce actions in parse table.
void reduces(StateSet T);

typedef SymTable SymbolSet;
typedef Node SymbolNode;

// Adds reduce action in state with hash hsh for all terminals in S.
void addrdc(int p, key hsh, SymbolSet S);

// Insert hash of symbol X into hash.
void symbolhash(symbol *X, key hash);

// Equality comparison for symbols.
bool symboleq(symbol s1, symbol s2);

// Inserts FIRST(X) into S.
void first(symbol X, SymbolSet S);

// Inserts FOLLOW(X) into S.
void follow(symbol X, SymbolSet S);