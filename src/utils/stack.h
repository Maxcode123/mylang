#pragma once

#include "list.h"

// Head node.
typedef Node Stack; 

Stack stack();

Node stk_pop(Stack *s);

void stk_push(Node n, Stack *s);

void stk_clear(Stack *s);