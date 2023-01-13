#pragma once

#include "list.h"

// Head node.
typedef Node Stack; 

Stack stack();

Node pop(Stack *s);

void push(Node n, Stack *s);

void clear(Stack *s);