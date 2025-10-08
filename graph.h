#ifndef GRAPH_H
#define GRAPH_H

#include "dynamicArray.h"
#include "hashmap.h"
#include <stddef.h>

typedef struct GraphVertex GraphVertex;

typedef struct Edge{
    GraphVertex* neighbour;
    int weight;
} EdgeT;

struct GraphVertex{
    int id;
    DynamicArrayT* edges;
};

typedef struct Graph{
    DynamicArrayT* vertices;
    size_t num_vertices;
    size_t num_edges;
    HashmapT* id_to_index_map;
} GraphT;

// Returns a pointer to a graph on success, NULL if memory allocation failed
GraphT* graph_create();
// Returns 0 on success, -1 if parsed NULL parameter
int graph_destroy(GraphT* graph);
// Returns 0 on success, -1 if memory allocation failed
int graph_add_vertex(GraphT* graph, int vertex_id);
// Returns 0 on success, -1 if parsed NULL parameter or memory allocation failed, -2 if failed to find vertex
int graph_add_edge(GraphT* graph, int from_vertex_id, int to_vertex_id, int weight);
// Returns 0 on success, -1 if parsed NULL parameter, -2 if failed to find vertex
int graph_print_neighbours(GraphT* graph, int vertex_id);
// Returns 0 on success, -1 if parsed NULL parameter or memory allocation failed, -2 if failed to get hashmap
int graph_BFS(GraphT* graph, int source_vertex_id);

#endif