#include "disjoint_set.h"

#include <stdint.h>
#include <stdlib.h>

struct DisjointSetNode {
    size_t parent;
    size_t size;
};

bool disjoint_set_init(DisjointSet *set, size_t size)
{
    *set = (DisjointSet){0};
    if (size > SIZE_MAX / sizeof *set->nodes)
        return false;

    if (size != 0)
    {
        set->nodes = malloc(size * sizeof *set->nodes);
        if (set->nodes == NULL)
            return false;
    }

    for (size_t i = 0; i < size; i++)
        set->nodes[i] = (DisjointSetNode){i, 1};
    set->size = size;
    set->components = size;
    return true;
}

bool disjoint_set_find(DisjointSet *set, size_t item, size_t *root)
{
    if (item >= set->size || root == NULL)
        return false;

    while (item != set->nodes[item].parent)
    {
        size_t parent = set->nodes[item].parent;
        set->nodes[item].parent = set->nodes[parent].parent;
        item = set->nodes[item].parent;
    }
    *root = item;
    return true;
}

bool disjoint_set_union(DisjointSet *set, size_t first, size_t second)
{
    size_t a;
    size_t b;
    if (first >= set->size || second >= set->size)
        return false;

    disjoint_set_find(set, first, &a);
    disjoint_set_find(set, second, &b);
    if (a == b)
        return true;

    if (set->nodes[a].size < set->nodes[b].size)
    {
        size_t smaller = a;
        a = b;
        b = smaller;
    }
    set->nodes[b].parent = a;
    set->nodes[a].size += set->nodes[b].size;
    set->components--;
    return true;
}

void disjoint_set_free(DisjointSet *set)
{
    free(set->nodes);
    *set = (DisjointSet){0};
}
