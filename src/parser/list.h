#pragma once

#include <stdbool.h>
#include <string.h>

#include "grammar.h"


typedef struct _Node {
    key k;
    void *i;
    struct _Node *next;    
} *Node;

/* Node constructor; allocates memory for a Node and returns a pointer to a 
Node with the given values. */
Node node(key k, LR0_Item i);

// Equality comparison between ItemNodes of the same list.
bool inodeeq(Node in1, Node in2);

// Equality comparison between ItemNodes.
bool ninodeeq(Node in1, Node in2);

/* Linked list constructor; returns the pointer to the head of the list with
the initialization value. */
Node list();

// Adds a node to the linked list.
void add(Node n, Node* headptr);

/* Returns a pointer to the node in the list matching the given key. If there 
is no such Node, returns NULL. */
Node get(key k, Node head);

/* Substitutes the value of the Node with the given key. If there is no such
Node, returns false, otherwise returns true. */
bool subs(key k, LR0_Item i, Node head);

// Returns true if there exists a Node with key k, false otherwise.
bool haskey(key k, Node head);

// Clears list.
void clear(Node *headptr);

// Deletes head node, points head to next node.
void pop(Node *headptr);

// Inserts node after head. So head->next points to n.
void insert(Node* nptr, Node* headptr);