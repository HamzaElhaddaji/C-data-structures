#include "graph.h"

#include <stdint.h>
#include <stdlib.h>

struct GraphEdge {
    size_t to;
    GraphEdge *next;
};

bool graph_init(Graph *graph, size_t vertices, bool directed)
{
    *graph = (Graph){0};
    if (vertices > SIZE_MAX / sizeof *graph->adjacency)
        return false;

    if (vertices != 0)
    {
        graph->adjacency = malloc(vertices * sizeof *graph->adjacency);
        if (graph->adjacency == NULL)
            return false;
    }

    for (size_t i = 0; i < vertices; i++)
        graph->adjacency[i] = NULL;
    graph->vertices = vertices;
    graph->directed = directed;
    return true;
}

bool graph_has_edge(const Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertices || to >= graph->vertices)
        return false;

    const GraphEdge *edge = graph->adjacency[from];
    while (edge != NULL && edge->to != to)
        edge = edge->next;
    return edge != NULL;
}

bool graph_add_edge(Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertices || to >= graph->vertices)
        return false;
    if (graph_has_edge(graph, from, to))
        return true;

    GraphEdge *forward = malloc(sizeof *forward);
    if (forward == NULL)
        return false;

    if (!graph->directed && from != to)
    {
        GraphEdge *reverse = malloc(sizeof *reverse);
        if (reverse == NULL)
        {
            free(forward);
            return false;
        }
        *reverse = (GraphEdge){from, graph->adjacency[to]};
        graph->adjacency[to] = reverse;
    }

    *forward = (GraphEdge){to, graph->adjacency[from]};
    graph->adjacency[from] = forward;
    return true;
}

static bool remove_edge(GraphEdge **link, size_t to)
{
    while (*link != NULL && (*link)->to != to)
        link = &(*link)->next;
    if (*link == NULL)
        return false;

    GraphEdge *edge = *link;
    *link = edge->next;
    free(edge);
    return true;
}

bool graph_remove_edge(Graph *graph, size_t from, size_t to)
{
    if (from >= graph->vertices || to >= graph->vertices ||
        !remove_edge(&graph->adjacency[from], to))
        return false;

    if (!graph->directed && from != to)
        remove_edge(&graph->adjacency[to], from);
    return true;
}

size_t graph_bfs(const Graph *graph, size_t start, size_t *order, size_t capacity)
{
    if (start >= graph->vertices || order == NULL || capacity < graph->vertices)
        return 0;

    unsigned char *visited = calloc(graph->vertices, sizeof *visited);
    if (visited == NULL)
        return 0;

    size_t count = 1;
    order[0] = start;
    visited[start] = 1;
    for (size_t i = 0; i < count; i++)
    {
        for (const GraphEdge *edge = graph->adjacency[order[i]];
             edge != NULL; edge = edge->next)
        {
            if (!visited[edge->to])
            {
                visited[edge->to] = 1;
                order[count++] = edge->to;
            }
        }
    }

    free(visited);
    return count;
}

void graph_free(Graph *graph)
{
    for (size_t i = 0; i < graph->vertices; i++)
    {
        GraphEdge *edge = graph->adjacency[i];
        while (edge != NULL)
        {
            GraphEdge *next = edge->next;
            free(edge);
            edge = next;
        }
    }
    free(graph->adjacency);
    *graph = (Graph){0};
}
