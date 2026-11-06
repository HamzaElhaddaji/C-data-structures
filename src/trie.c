#include "trie.h"

#include <stdlib.h>

struct TrieNode {
    unsigned char byte;
    bool terminal;
    TrieNode *children;
    TrieNode *next;
};

void trie_init(Trie *trie)
{
    *trie = (Trie){0};
}

static void free_nodes(TrieNode *node)
{
    while (node != NULL)
    {
        TrieNode *next = node->next;
        if (node->children != NULL)
        {
            // Put the children before the pending siblings for iterative cleanup.
            TrieNode *tail = node->children;
            while (tail->next != NULL)
                tail = tail->next;
            tail->next = next;
            next = node->children;
        }
        free(node);
        node = next;
    }
}

static const TrieNode *find_node(const Trie *trie, const char *word)
{
    const TrieNode *children = trie->children;
    const TrieNode *node = NULL;
    for (; *word != '\0'; word++)
    {
        node = children;
        while (node != NULL && node->byte != (unsigned char)*word)
            node = node->next;
        if (node == NULL)
            return NULL;
        children = node->children;
    }
    return node;
}

bool trie_contains(const Trie *trie, const char *word)
{
    if (word == NULL)
        return false;
    if (*word == '\0')
        return trie->has_empty_word;

    const TrieNode *node = find_node(trie, word);
    return node != NULL && node->terminal;
}

bool trie_has_prefix(const Trie *trie, const char *prefix)
{
    if (prefix == NULL)
        return false;
    return *prefix == '\0' ? trie->size != 0 : find_node(trie, prefix) != NULL;
}

bool trie_insert(Trie *trie, const char *word)
{
    if (word == NULL)
        return false;

    bool *terminal = &trie->has_empty_word;
    TrieNode **link = &trie->children;
    while (*word != '\0')
    {
        while (*link != NULL && (*link)->byte != (unsigned char)*word)
            link = &(*link)->next;
        if (*link == NULL)
            break;
        terminal = &(*link)->terminal;
        link = &(*link)->children;
        word++;
    }

    TrieNode *suffix = NULL;
    TrieNode **tail = &suffix;
    for (; *word != '\0'; word++)
    {
        TrieNode *node = malloc(sizeof *node);
        if (node == NULL)
        {
            free_nodes(suffix);
            return false;
        }
        *node = (TrieNode){(unsigned char)*word, false, NULL, NULL};
        *tail = node;
        tail = &node->children;
        terminal = &node->terminal;
    }
    if (suffix != NULL)
        *link = suffix;
    if (!*terminal)
    {
        *terminal = true;
        trie->size++;
    }
    return true;
}

bool trie_remove(Trie *trie, const char *word)
{
    if (word == NULL)
        return false;
    if (*word == '\0')
    {
        if (!trie->has_empty_word)
            return false;
        trie->has_empty_word = false;
        trie->size--;
        return true;
    }

    TrieNode **children = &trie->children;
    TrieNode **prune = NULL;
    TrieNode *node = NULL;
    for (; *word != '\0'; word++)
    {
        TrieNode **link = children;
        while (*link != NULL && (*link)->byte != (unsigned char)*word)
            link = &(*link)->next;
        if (*link == NULL)
            return false;

        // Keep the parent when another word ends or branches here.
        if (node == NULL || node->terminal || link != children || (*link)->next != NULL)
            prune = link;
        node = *link;
        children = &node->children;
    }

    if (!node->terminal)
        return false;

    node->terminal = false;
    trie->size--;
    if (node->children == NULL)
    {
        TrieNode *suffix = *prune;
        *prune = suffix->next;
        suffix->next = NULL;
        free_nodes(suffix);
    }
    return true;
}

void trie_free(Trie *trie)
{
    free_nodes(trie->children);
    trie_init(trie);
}
