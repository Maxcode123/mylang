#pragma once

#include <stdbool.h>
#include <string.h>

#include "util.h"

typedef struct _Node {
    key k;
    void *i;
    struct _Node *next;    
} *Node;

typedef void *ListItem;

/* Node constructor; allocates memory for a Node and returns a pointer to a 
Node with the given values. */
Node node(key k, ListItem i);

// Equality comparison between Nodes of the same list.
bool lnodeeq(Node in1, Node in2, bool (*ieq)(ListItem, ListItem));

// Equality comparison between Nodes.
bool nodeeq(Node in1, Node in2, bool (*ieq)(ListItem, ListItem));

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
bool subs(key k, ListItem, Node head);

// Returns true if there exists a Node with key k, false otherwise.
bool haskey(key k, Node head);

// Clears list.
void clear(Node *headptr);

// Deletes head node, points head to next node.
void pop(Node *headptr);

// Inserts node after head. So head->next points to n.
void insert(Node *nptr, Node *headptr);

// Inserts node pointed at by nptr after node n.
void insertat(Node *nptr, Node head, Node *n, bool (*ieq)(ListItem, ListItem));

// Returns list length
int len(Node head);