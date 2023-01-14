#pragma once

#include "list.h"

// Head node.
typedef Node Stack; 

/* Stack constructor; returns the pointer to the head of the stack with
the initialization value. */
Stack stk_stack();

// Pops the top of the stack and returns it.
Node stk_pop(Stack *sptr);

// Pushes given node to top of stack.
void stk_push(Node n, Stack *sptr);

// Clears whole stack.
void stk_clear(Stack *sptr);

// Returns stack length.
int stk_len(Stack s);

// Prints the stack keys horizontally.
void stk_printk(Stack s);