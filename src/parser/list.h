#pragma once

#include <stdbool.h>
#include <string.h>

#include "grammar.h"


typedef struct _LR0_ItemNode {
    key k;
    LR0_Item i;
    struct _LR0_ItemNode *next;    
} *LR0_ItemNode;

/* Node constructor; allocates memory for a Node and returns a pointer to a 
Node with the given values. */
LR0_ItemNode LR0_node(key k, LR0_Item i);

// Equality comparison between ItemNodes
bool LR0_inodeeq(LR0_ItemNode in1, LR0_ItemNode in2);

/* Linked list constructor; returns the pointer to the head of the list with
the initialization value. */
LR0_ItemNode LR0_list();

// Adds a node to the linked list.
void LR0_add(LR0_ItemNode n, LR0_ItemNode* headptr);

/* Returns a pointer to the node in the list matching the given key. If there 
is no such Node, returns NULL. */
LR0_ItemNode LR0_get(key k, LR0_ItemNode head);

/* Substitutes the value of the Node with the given key. If there is no such
Node, returns false, otherwise returns true. */
bool LR0_subs(key k, LR0_Item i, LR0_ItemNode head);

// Returns true if there exists a Node with key k, false otherwise.
bool LR0_haskey(key k, LR0_ItemNode head);

// Clears list.
void LR0_clear(LR0_ItemNode *headptr);

// Deletes head node, points head to next node.
void LR0_pop(LR0_ItemNode *headptr);