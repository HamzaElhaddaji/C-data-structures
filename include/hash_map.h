#ifndef CDS_HASH_MAP_H
#define CDS_HASH_MAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct HashEntry HashEntry;

typedef struct {
    HashEntry **buckets;
    size_t capacity;
    size_t size;
} HashMap;

void hash_map_init(HashMap *map);
bool hash_map_put(HashMap *map, int key, int value);
bool hash_map_get(const HashMap *map, int key, int *value);
bool hash_map_remove(HashMap *map, int key);
void hash_map_free(HashMap *map);

#endif
