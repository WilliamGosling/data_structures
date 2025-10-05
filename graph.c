#include "graph.h"

GraphT* graph_create(){

    GraphT* graph = malloc(sizeof(GraphT));
    if(graph == NULL){
        return NULL;
    }
    graph->vertices = dynamic_array_create(10);
    if(graph->vertices == NULL){
        free(graph);
        return NULL;
    }

    graph->num_edges = 0;
    graph->num_vertices = 0;
    return graph;
}

int graph_destroy(GraphT* graph){

    if(graph == NULL){
        return -1;
    }

    for(size_t i = 0;i < graph->num_vertices;i++){
        GraphVertex* vertex = &graph->vertices->data[i];
        dynamic_array_destroy(vertex->edges);
    }
    dynamic_array_destroy(graph->vertices);
    free(graph);
    return 0;
}

int graph_add_vertex(GraphT* graph, int vertex_id){

    if(graph == NULL){
        return -1;
    }

    GraphVertex* vertex;
    vertex->id = vertex_id;
    vertex->edges = dynamic_array_create(5);
    if(vertex->edges == NULL){
        return -1;
    }

    if(dynamic_array_append(graph->vertices, &vertex) == -1){
        dynamic_array_destroy(vertex->edges);
        return -1;
    }
    
    graph->num_vertices++;
    return 0;
}