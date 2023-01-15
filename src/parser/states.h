#pragma once

#include "operations.h"

typedef ItemSet State; // A state is a set of items.
typedef SymTable StateSet;
typedef SymTable EdgeSet;
typedef Node StateNode;
typedef Node EdgeNode;

typedef struct _Edge {
    symbol X;
    State from;
    State to;
} *Edge;

// Edge contstructor, allocates memory for edge.
Edge edge(symbol X, State from, State to);

// Inserts hash of edge into hash.
void edgehash(Edge e, key hash);

// Prints edge as, {from hash} -> {to hash}, {symbol}
void printedge(Edge e); 

/* Calculates states and edges and inserts them into T and E respectively.
T is a set of States, E is a set of Edges. */
void states(StateSet T, EdgeSet E);

// Inserts initial state into T.
void stateinit(StateSet T);

// Equality comparison between two states.
bool stateeq(State I1, State I2);

// Inserts hash of state t into hash.
void statehash(State I, key hash);

// Prints items of state.
void printstate(State I);