#pragma once

#include <stdbool.h>
#include <string.h>

#include "grammar.h"

typedef char *key;

typedef struct _ItemNode {
    key k;
    Item i;
    struct _ItemNode *next;    
} *ItemNode;

/* Node constructor; allocates memory for a Node and returns a pointer to a 
Node with the given values. */
ItemNode node(key k, Item i);

// Equality comparison between ItemNodes
bool inodeeq(ItemNode in1, ItemNode in2);

/* Linked list constructor; returns the pointer to the head of the list with
the initialization value. */
ItemNode list();

// Adds a node to the linked list.
void addin(ItemNode n, ItemNode* headptr);

/* Returns a pointer to the node in the list matching the given key. If there 
is no such Node, returns NULL. */
ItemNode getin(key k, ItemNode head);

/* Substitutes the value of the Node with the given key. If there is no such
Node, returns false, otherwise returns true. */
bool subs(key k, Item i, ItemNode head);
