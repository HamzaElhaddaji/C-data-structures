#ifndef CDS_DISJOINT_SET_H
#define CDS_DISJOINT_SET_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DisjointSetNode DisjointSetNode;

typedef struct {
    DisjointSetNode *nodes;
    size_t size;
    size_t components;
} DisjointSet;

bool disjoint_set_init(DisjointSet *set, size_t size);
bool disjoint_set_find(DisjointSet *set, size_t item, size_t *root);
bool disjoint_set_union(DisjointSet *set, size_t first, size_t second);
void disjoint_set_free(DisjointSet *set);

#endif
