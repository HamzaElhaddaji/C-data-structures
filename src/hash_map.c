#include "hash_map.h"

#include <stdint.h>
#include <stdlib.h>

struct HashEntry {
    int key;
    int value;
    HashEntry *next;
};

void hash_map_init(HashMap *map)
{
    *map = (HashMap){0};
}

static size_t bucket_for(int key, size_t capacity)
{
    uintmax_t hash = (unsigned int)key;
    hash ^= hash >> 16;
    hash *= UINTMAX_C(0x7feb352d);
    hash ^= hash >> 15;
    return (size_t)(hash % capacity);
}

static HashEntry *find_entry(const HashMap *map, int key)
{
    if (map->capacity == 0)
        return NULL;

    HashEntry *entry = map->buckets[bucket_for(key, map->capacity)];
    while (entry != NULL && entry->key != key)
        entry = entry->next;
    return entry;
}

static bool grow(HashMap *map)
{
    const size_t limit = SIZE_MAX / sizeof *map->buckets;
    if (map->capacity > limit / 2)
        return false;

    size_t capacity = map->capacity == 0 ? 8 : map->capacity * 2;
    if (capacity > limit)
        return false;

    HashEntry **buckets = malloc(capacity * sizeof *buckets);
    if (buckets == NULL)
        return false;

    for (size_t i = 0; i < capacity; i++)
        buckets[i] = NULL;
    for (size_t i = 0; i < map->capacity; i++)
    {
        HashEntry *entry = map->buckets[i];
        while (entry != NULL)
        {
            HashEntry *next = entry->next;
            size_t bucket = bucket_for(entry->key, capacity);
            entry->next = buckets[bucket];
            buckets[bucket] = entry;
            entry = next;
        }
    }
    free(map->buckets);
    map->buckets = buckets;
    map->capacity = capacity;
    return true;
}

bool hash_map_put(HashMap *map, int key, int value)
{
    HashEntry *entry = find_entry(map, key);
    if (entry != NULL)
    {
        entry->value = value;
        return true;
    }

    entry = malloc(sizeof *entry);
    if (entry == NULL)
        return false;
    if (map->size == map->capacity && !grow(map))
    {
        free(entry);
        return false;
    }

    size_t bucket = bucket_for(key, map->capacity);
    *entry = (HashEntry){key, value, map->buckets[bucket]};
    map->buckets[bucket] = entry;
    map->size++;
    return true;
}

bool hash_map_get(const HashMap *map, int key, int *value)
{
    const HashEntry *entry = find_entry(map, key);
    if (entry == NULL || value == NULL)
        return false;

    *value = entry->value;
    return true;
}

bool hash_map_remove(HashMap *map, int key)
{
    if (map->capacity == 0)
        return false;

    HashEntry **link = &map->buckets[bucket_for(key, map->capacity)];
    while (*link != NULL && (*link)->key != key)
        link = &(*link)->next;
    if (*link == NULL)
        return false;

    HashEntry *entry = *link;
    *link = entry->next;
    free(entry);
    map->size--;
    return true;
}

void hash_map_free(HashMap *map)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        HashEntry *entry = map->buckets[i];
        while (entry != NULL)
        {
            HashEntry *next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    hash_map_init(map);
}
