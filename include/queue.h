#ifndef CDS_QUEUE_H
#define CDS_QUEUE_H

#include "deque.h"

typedef struct {
    Deque items;
} Queue;

void queue_init(Queue *queue);
bool queue_enqueue(Queue *queue, int value);
bool queue_dequeue(Queue *queue, int *value);
bool queue_peek(const Queue *queue, int *value);
size_t queue_size(const Queue *queue);
void queue_free(Queue *queue);

#endif
