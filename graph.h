#ifndef GRAPH_H
#define GRAPH_H

#include "dynamicArray.h"
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
} GraphT;



#endif