#include "deque.h"

#include <stdint.h>
#include <stdlib.h>

struct DequeNode {
    int value;
    DequeNode *previous;
    DequeNode *next;
};

void deque_init(Deque *deque)
{
    *deque = (Deque){0};
}

static bool insert_between(Deque *deque, DequeNode *previous, DequeNode *next,
                           int value)
{
    if (deque->size == SIZE_MAX)
        return false;

    DequeNode *node = malloc(sizeof *node);
    if (node == NULL)
        return false;

    *node = (DequeNode){value, previous, next};
    if (previous != NULL)
        previous->next = node;
    else
        deque->front = node;
    if (next != NULL)
        next->previous = node;
    else
        deque->back = node;
    deque->size++;
    return true;
}

bool deque_push_front(Deque *deque, int value)
{
    return insert_between(deque, NULL, deque->front, value);
}

bool deque_push_back(Deque *deque, int value)
{
    return insert_between(deque, deque->back, NULL, value);
}

static bool read_node(const DequeNode *node, int *value)
{
    if (node == NULL || value == NULL)
        return false;

    *value = node->value;
    return true;
}

bool deque_peek_front(const Deque *deque, int *value)
{
    return read_node(deque->front, value);
}

bool deque_peek_back(const Deque *deque, int *value)
{
    return read_node(deque->back, value);
}

static bool remove_node(Deque *deque, DequeNode *node, int *value)
{
    if (!read_node(node, value))
        return false;

    if (node->previous != NULL)
        node->previous->next = node->next;
    else
        deque->front = node->next;
    if (node->next != NULL)
        node->next->previous = node->previous;
    else
        deque->back = node->previous;
    free(node);
    deque->size--;
    return true;
}

bool deque_pop_front(Deque *deque, int *value)
{
    return remove_node(deque, deque->front, value);
}

bool deque_pop_back(Deque *deque, int *value)
{
    return remove_node(deque, deque->back, value);
}

static DequeNode *node_at(const Deque *deque, size_t index)
{
    if (index >= deque->size)
        return NULL;

    if (index < deque->size / 2)
    {
        DequeNode *node = deque->front;
        for (size_t i = 0; i < index; i++)
            node = node->next;
        return node;
    }

    DequeNode *node = deque->back;
    for (size_t i = deque->size - 1; i > index; i--)
        node = node->previous;
    return node;
}

bool deque_get(const Deque *deque, size_t index, int *value)
{
    return read_node(node_at(deque, index), value);
}

bool deque_insert(Deque *deque, size_t index, int value)
{
    if (index == deque->size)
        return deque_push_back(deque, value);

    DequeNode *next = node_at(deque, index);
    return next != NULL && insert_between(deque, next->previous, next, value);
}

bool deque_remove(Deque *deque, size_t index, int *value)
{
    return remove_node(deque, node_at(deque, index), value);
}

void deque_free(Deque *deque)
{
    int unused;
    while (deque_pop_front(deque, &unused))
        continue;
}
