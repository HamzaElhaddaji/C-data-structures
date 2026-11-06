#include "queue.h"

void queue_init(Queue *queue)
{
    deque_init(&queue->items);
}

bool queue_enqueue(Queue *queue, int value)
{
    return deque_push_back(&queue->items, value);
}

bool queue_dequeue(Queue *queue, int *value)
{
    return deque_pop_front(&queue->items, value);
}

bool queue_peek(const Queue *queue, int *value)
{
    return deque_peek_front(&queue->items, value);
}

size_t queue_size(const Queue *queue)
{
    return queue->items.size;
}

void queue_free(Queue *queue)
{
    deque_free(&queue->items);
}
