#ifndef CDS_GRAPH_H
#define CDS_GRAPH_H

#include <stdbool.h>
#include <stddef.h>

typedef struct GraphEdge GraphEdge;

typedef struct {
    GraphEdge **adjacency;
    size_t vertices;
    bool directed;
} Graph;

bool graph_init(Graph *graph, size_t vertices, bool directed);
bool graph_has_edge(const Graph *graph, size_t from, size_t to);
bool graph_add_edge(Graph *graph, size_t from, size_t to);
bool graph_remove_edge(Graph *graph, size_t from, size_t to);
/* order must have room for vertices entries. Returns the number visited, or 0 on failure. */
size_t graph_bfs(const Graph *graph, size_t start, size_t *order, size_t capacity);
void graph_free(Graph *graph);

#endif
