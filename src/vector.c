#include "vector.h"
#include "int_storage.h"

#include <string.h>

void vector_init(Vector *vector)
{
    *vector = (Vector){0};
}

bool vector_get(const Vector *vector, size_t index, int *value)
{
    if (index >= vector->size || value == NULL)
        return false;

    *value = vector->data[index];
    return true;
}

bool vector_set(Vector *vector, size_t index, int value)
{
    if (index >= vector->size)
        return false;

    vector->data[index] = value;
    return true;
}

bool vector_insert(Vector *vector, size_t index, int value)
{
    if (index > vector->size)
        return false;
    if (vector->size == vector->capacity &&
        !int_storage_grow(&vector->data, &vector->capacity))
        return false;

    int *slot = &vector->data[index];
    memmove(slot + 1, slot, (vector->size - index) * sizeof *slot);
    *slot = value;
    vector->size++;
    return true;
}

bool vector_push(Vector *vector, int value)
{
    return vector_insert(vector, vector->size, value);
}

bool vector_remove(Vector *vector, size_t index, int *value)
{
    if (!vector_get(vector, index, value))
        return false;

    int *slot = &vector->data[index];
    vector->size--;
    memmove(slot, slot + 1, (vector->size - index) * sizeof *slot);
    return true;
}

void vector_free(Vector *vector)
{
    free(vector->data);
    vector_init(vector);
}
