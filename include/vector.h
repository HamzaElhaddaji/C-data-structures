#ifndef CDS_VECTOR_H
#define CDS_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *vector);
bool vector_get(const Vector *vector, size_t index, int *value);
bool vector_set(Vector *vector, size_t index, int value);
bool vector_insert(Vector *vector, size_t index, int value);
bool vector_push(Vector *vector, int value);
bool vector_remove(Vector *vector, size_t index, int *value);
void vector_free(Vector *vector);

#endif
