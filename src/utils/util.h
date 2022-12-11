#pragma once

#include <assert.h>

typedef char *string;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);
