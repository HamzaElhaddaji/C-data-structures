#ifndef CDS_MIN_HEAP_H
#define CDS_MIN_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

void min_heap_init(MinHeap *heap);
bool min_heap_push(MinHeap *heap, int value);
bool min_heap_peek(const MinHeap *heap, int *value);
bool min_heap_pop(MinHeap *heap, int *value);
void min_heap_free(MinHeap *heap);

#endif
