#ifndef CDS_DEQUE_H
#define CDS_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DequeNode DequeNode;

typedef struct {
    DequeNode *front;
    DequeNode *back;
    size_t size;
} Deque;

void deque_init(Deque *deque);
bool deque_push_front(Deque *deque, int value);
bool deque_push_back(Deque *deque, int value);
bool deque_peek_front(const Deque *deque, int *value);
bool deque_peek_back(const Deque *deque, int *value);
bool deque_pop_front(Deque *deque, int *value);
bool deque_pop_back(Deque *deque, int *value);
bool deque_get(const Deque *deque, size_t index, int *value);
bool deque_insert(Deque *deque, size_t index, int value);
bool deque_remove(Deque *deque, size_t index, int *value);
void deque_free(Deque *deque);

#endif
