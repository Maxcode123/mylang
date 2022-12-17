#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef char *string;
typedef char *key;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

// Sort integer array
void sorti(int *, size_t);

// Comparator function used to sort.
int cmp(int *, int *);
