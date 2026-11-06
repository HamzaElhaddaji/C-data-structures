#ifndef CDS_INT_STORAGE_H
#define CDS_INT_STORAGE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static inline bool int_storage_grow(int **data, size_t *capacity)
{
    const size_t limit = SIZE_MAX / sizeof **data;
    if (*capacity == limit)
        return false;

    size_t next = *capacity == 0 ? 1 : *capacity;
    next = next <= limit / 2 ? next * 2 : limit;
    int *buffer = realloc(*data, next * sizeof *buffer);
    if (buffer == NULL)
        return false;

    *data = buffer;
    *capacity = next;
    return true;
}

#endif
