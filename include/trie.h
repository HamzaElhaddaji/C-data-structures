#ifndef CDS_TRIE_H
#define CDS_TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct TrieNode TrieNode;

typedef struct {
    TrieNode *children;
    size_t size;
    bool has_empty_word;
} Trie;

void trie_init(Trie *trie);
bool trie_insert(Trie *trie, const char *word);
bool trie_contains(const Trie *trie, const char *word);
bool trie_has_prefix(const Trie *trie, const char *prefix);
bool trie_remove(Trie *trie, const char *word);
void trie_free(Trie *trie);

#endif
