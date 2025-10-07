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
    graph->id_to_index_map = hashmap_create(0);
    if(graph->id_to_index_map == NULL){
        free(graph->vertices);
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
    char vertex_str_id[128];
    snprintf(vertex_str_id, sizeof(vertex_str_id), "%d", vertex_id);
    if(hashmap_has_key(graph->id_to_index_map, vertex_str_id)){
        return 0;
    }

    GraphVertex vertex;
    vertex.id = vertex_id;
    vertex.edges = dynamic_array_create(5);
    if(vertex.edges == NULL){
        return -1;
    }

    if(dynamic_array_append(graph->vertices, &vertex) == -1){
        dynamic_array_destroy(vertex.edges);
        return -1;
    }
    
    size_t index = graph->num_vertices - 1;
    hashmap_set(graph->id_to_index_map, vertex_str_id, (void*)index);
    graph->num_vertices++;

    return 0;
}

int graph_add_edge(GraphT* graph, int from_vertex_id, int to_vertex_id, int weight){

    if(graph == NULL){
        return -1;
    }

    GraphVertex* start_vertex = graph_find_vertex(graph, from_vertex_id);
    GraphVertex* end_vertex = graph_find_vertex(graph, to_vertex_id); 
    if(start_vertex == NULL || end_vertex == NULL){
        return -1;
    }


    EdgeT edge;
    edge.weight = weight;
    edge.neighbour = end_vertex;
    if(dynamic_array_append(start_vertex->edges, &edge) == -1){
        return -1;
    }
    
    graph->num_edges++;
    return 0;
}

static GraphVertex* graph_find_vertex(GraphT* graph, int vertex_id){

    if(graph == NULL){
        return NULL;
    }

    GraphVertex* vertex = hashmap_get(graph->id_to_index_map, vertex_id);
    if(vertex == NULL){
        return NULL;
    }
    return vertex;

    for(size_t i = 0;i < graph->num_vertices;i++){
        GraphVertex* vertex = (GraphVertex*)dynamic_array_get_element_ptr(graph->vertices, i);
        if(vertex->id == vertex_id){
            return vertex;
        }
    }
    return NULL;
}

int graph_print_neighbours(GraphT* graph, int vertex_id){

    if(graph == NULL){
        return -1;
    }
    GraphVertex* vertex = graph_find_vertex(graph, vertex_id);
    if(vertex == NULL){
        return -1;
    }
    printf("Neighbours of vertex %d\n", vertex_id);

    for(size_t i = 0;i < vertex->edges->size; i++){
        EdgeT* edge = (EdgeT*)dynamic_array_get_element_ptr(vertex->edges, i);
        int neighbour_id = edge->neighbour->id;
        printf(" ID: %d Weight: %d\n", neighbour_id, edge->weight);

    }
    return 0;
}

int graph_BFS(GraphT* graph, GraphVertex* source_vertex){

    DynamicArrayT* queue = dynamic_array_create(graph->num_vertices);
    


}