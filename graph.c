#include "graph.h"

static GraphVertex* graph_find_vertex(GraphT* graph, int vertex_id);

GraphT* graph_create(){

    GraphT* graph = malloc(sizeof(GraphT));
    if(graph == NULL){
        return NULL;
    }
    graph->vertices = dynamic_array_create(10, sizeof(GraphVertex));
    if(graph->vertices == NULL){
        free(graph);
        return NULL;
    }
    graph->id_to_index_map = hashmap_create(0);
    if(graph->id_to_index_map == NULL){
        dynamic_array_destroy(graph->vertices);
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
        GraphVertex* vertex = dynamic_array_get_element_ptr(graph->vertices, i);
        if(vertex != NULL){
            dynamic_array_destroy(vertex->edges);
        }
    }
    dynamic_array_destroy(graph->vertices);
    hashmap_destroy(graph->id_to_index_map);
    free(graph);
    return 0;
}

int graph_add_vertex(GraphT* graph, int vertex_id){

    if(graph == NULL){
        return -1;
    }
    char vertex_str_id[32];
    snprintf(vertex_str_id, sizeof(vertex_str_id), "%d", vertex_id);
    if(hashmap_has_key(graph->id_to_index_map, vertex_str_id)){
        return 0;
    }

    GraphVertex vertex;
    vertex.id = vertex_id;
    vertex.edges = dynamic_array_create(5, sizeof(EdgeT));
    if(vertex.edges == NULL){
        return -1;
    }

    if(dynamic_array_append(graph->vertices, &vertex) == -1){
        dynamic_array_destroy(vertex.edges);
        return -1;
    }
    
    size_t index = graph->vertices->size - 1;
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
        return -2;
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

    char vertex_str_id[32];
    snprintf(vertex_str_id, sizeof(vertex_str_id), "%d", vertex_id);

    void* temp = hashmap_get(graph->id_to_index_map, vertex_str_id);
    if(temp == NULL){
        return NULL;
    }
    size_t index = (size_t)temp;
    return dynamic_array_get_element_ptr(graph->vertices, index);
}

int graph_print_neighbours(GraphT* graph, int vertex_id){

    if(graph == NULL){
        return -1;
    }
    GraphVertex* vertex = graph_find_vertex(graph, vertex_id);
    if(vertex == NULL){
        printf("Vertex %d not found\n", vertex_id);
        return -2;
    }
    printf("Neighbours of vertex %d\n", vertex_id);

    for(size_t i = 0;i < vertex->edges->size; i++){
        EdgeT* edge = (EdgeT*)dynamic_array_get_element_ptr(vertex->edges, i);
        int neighbour_id = edge->neighbour->id;
        printf(" ID: %d Weight: %d\n", neighbour_id, edge->weight);

    }
    return 0;
}

int graph_BFS(GraphT* graph, int source_vertex_id){

    if(graph == NULL){
        return -1;
    }

    char vertex_str_id[32];
    snprintf(vertex_str_id, sizeof(vertex_str_id), "%d",source_vertex_id);

    void* temp = hashmap_get(graph->id_to_index_map, vertex_str_id);
    if(temp == NULL){
        return -2;
    }
    size_t index = (size_t)temp;

    int* visited = calloc(graph->num_vertices, sizeof(int));
    DynamicArrayT* queue = dynamic_array_create(graph->num_vertices, sizeof(size_t));
    if(queue == NULL || visited == NULL){
        dynamic_array_destroy(queue);
        free(visited);
        return -1;
    }

    visited[index] = 1;

    if(dynamic_array_append(queue, &index) == -1){
        dynamic_array_destroy(queue);
        free(visited);
        return -1;
    }

    while(queue->size > 0){
        size_t current_index;
        dynamic_array_get(queue, 0, &current_index);
        dynamic_array_remove(queue, 0);

        GraphVertex* current_vertex = dynamic_array_get_element_ptr(graph->vertices, current_index);
        if(current_vertex != NULL){
            printf("Visited Vertex ID: %d\n", current_vertex->id);
        }

        for(size_t i = 0;i < current_vertex->edges->size;i++){
            EdgeT* edge = dynamic_array_get_element_ptr(current_vertex->edges, i);
            GraphVertex* neighbour_vertex = edge->neighbour;
            snprintf(vertex_str_id, sizeof(vertex_str_id), "%d", neighbour_vertex->id);
            size_t neighbour_index = (size_t)hashmap_get(graph->id_to_index_map, vertex_str_id);

            if(!visited[neighbour_index]){
                visited[neighbour_index] = 1;
                dynamic_array_append(queue, &neighbour_index);
            }
        }
    }

    dynamic_array_destroy(queue);
    free(visited);
    return 0;
}