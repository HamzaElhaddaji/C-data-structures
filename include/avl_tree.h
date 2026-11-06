#ifndef CDS_AVL_TREE_H
#define CDS_AVL_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct AvlNode AvlNode;

typedef struct {
    AvlNode *root;
    size_t size;
} AvlTree;

void avl_init(AvlTree *tree);
bool avl_contains(const AvlTree *tree, int value);
bool avl_insert(AvlTree *tree, int value);
bool avl_remove(AvlTree *tree, int value);
void avl_free(AvlTree *tree);

#endif
