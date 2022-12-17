#pragma once

#include "operations.h"

typedef SymTable State; // A state is a set of items.

typedef struct _Edge {
    symbol X;
    State from;
    State to;
} *Edge;

// Edge contstructor, allocates memory for edge.
Edge edge(symbol X, State from, State to);

// Inserts hash of edge into hash.
void edgehash(Edge e, key hash);

/* Calculates states and edges and inserts them into T and E respectively.
T is a set of States, E is a set of Edges. */
void states(SymTable T, SymTable E);

// Inserts initial state into T.
void stateinit(SymTable T);

// Equality comparison between two states.
bool stateeq(State I1, State I2);

// Inserts hash of state t into hash.
void statehash(State I, key hash);