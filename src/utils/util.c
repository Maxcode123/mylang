#include "util.h"

void *checked_malloc(int len) {
    void *p = malloc(len);
    if (!p) {
        fprintf(stderr,"\nRan out of memory!\n");
        exit(1);
    }
    return p;
}

string String(char *s) {
    string p = checked_malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

void sorti(int *a, size_t n) {
    qsort(a, n, sizeof(int), &cmp);
}

int cmp(int *a, int *b) {
    if (*a > *b) return 1;
    return 0;
}