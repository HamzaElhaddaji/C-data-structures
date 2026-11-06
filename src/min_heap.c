#include "min_heap.h"
#include "int_storage.h"

void min_heap_init(MinHeap *heap)
{
    *heap = (MinHeap){0};
}

bool min_heap_push(MinHeap *heap, int value)
{
    if (heap->size == heap->capacity &&
        !int_storage_grow(&heap->data, &heap->capacity))
        return false;

    size_t index = heap->size++;
    while (index > 0)
    {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] <= value)
            break;
        heap->data[index] = heap->data[parent];
        index = parent;
    }
    heap->data[index] = value;
    return true;
}

bool min_heap_peek(const MinHeap *heap, int *value)
{
    if (heap->size == 0 || value == NULL)
        return false;

    *value = heap->data[0];
    return true;
}

bool min_heap_pop(MinHeap *heap, int *value)
{
    if (!min_heap_peek(heap, value))
        return false;

    int last = heap->data[--heap->size];
    size_t index = 0;
    while (index < heap->size / 2)
    {
        size_t child = index * 2 + 1;
        size_t right = child + 1;
        if (right < heap->size && heap->data[right] < heap->data[child])
            child = right;
        if (last <= heap->data[child])
            break;
        heap->data[index] = heap->data[child];
        index = child;
    }
    heap->data[index] = last;
    return true;
}

void min_heap_free(MinHeap *heap)
{
    free(heap->data);
    min_heap_init(heap);
}
