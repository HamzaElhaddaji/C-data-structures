#include "avl_tree.h"

#include <stdlib.h>

struct AvlNode {
    int value;
    int height;
    AvlNode *left;
    AvlNode *right;
};

void avl_init(AvlTree *tree)
{
    *tree = (AvlTree){0};
}

static int height(const AvlNode *node)
{
    return node == NULL ? 0 : node->height;
}

static void update_height(AvlNode *node)
{
    int left = height(node->left);
    int right = height(node->right);
    node->height = 1 + (left > right ? left : right);
}

static AvlNode *rotate_left(AvlNode *node)
{
    AvlNode *root = node->right;
    node->right = root->left;
    root->left = node;
    update_height(node);
    update_height(root);
    return root;
}

static AvlNode *rotate_right(AvlNode *node)
{
    AvlNode *root = node->left;
    node->left = root->right;
    root->right = node;
    update_height(node);
    update_height(root);
    return root;
}

static AvlNode *rebalance(AvlNode *node)
{
    update_height(node);
    int balance = height(node->left) - height(node->right);
    if (balance > 1)
    {
        if (height(node->left->left) < height(node->left->right))
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1)
    {
        if (height(node->right->right) < height(node->right->left))
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

bool avl_contains(const AvlTree *tree, int value)
{
    const AvlNode *node = tree->root;
    while (node != NULL)
    {
        if (node->value == value)
            return true;
        node = value < node->value ? node->left : node->right;
    }
    return false;
}

static AvlNode *insert_node(AvlNode *node, int value, bool *inserted)
{
    if (node == NULL)
    {
        node = malloc(sizeof *node);
        if (node != NULL)
        {
            *node = (AvlNode){value, 1, NULL, NULL};
            *inserted = true;
        }
        return node;
    }

    if (value < node->value)
        node->left = insert_node(node->left, value, inserted);
    else if (value > node->value)
        node->right = insert_node(node->right, value, inserted);
    return rebalance(node);
}

bool avl_insert(AvlTree *tree, int value)
{
    bool inserted = false;
    tree->root = insert_node(tree->root, value, &inserted);
    if (inserted)
        tree->size++;
    return inserted;
}

static AvlNode *remove_node(AvlNode *node, int value, bool *removed)
{
    if (node == NULL)
        return NULL;

    if (value < node->value)
        node->left = remove_node(node->left, value, removed);
    else if (value > node->value)
        node->right = remove_node(node->right, value, removed);
    else
    {
        *removed = true;
        if (node->left == NULL || node->right == NULL)
        {
            AvlNode *child = node->left != NULL ? node->left : node->right;
            free(node);
            return child;
        }

        const AvlNode *successor = node->right;
        while (successor->left != NULL)
            successor = successor->left;
        node->value = successor->value;
        node->right = remove_node(node->right, node->value, removed);
    }
    return rebalance(node);
}

bool avl_remove(AvlTree *tree, int value)
{
    bool removed = false;
    tree->root = remove_node(tree->root, value, &removed);
    if (removed)
        tree->size--;
    return removed;
}

static void free_nodes(AvlNode *node)
{
    if (node == NULL)
        return;

    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
}

void avl_free(AvlTree *tree)
{
    free_nodes(tree->root);
    avl_init(tree);
}
