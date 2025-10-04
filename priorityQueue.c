#include "priorityQueue.h"

PriorityQueueT* pq_create(size_t initial_capacity){

    PriorityQueueT* queue = malloc(sizeof(PriorityQueueT));
    if(queue == NULL){
        return NULL;
    }

    if(initial_capacity == 0){
        queue->data = NULL;
    } else {
        queue->data = malloc(sizeof(int) * initial_capacity);
        if(queue->data == NULL){
            free(queue);
            return NULL;
        }
    }

    queue->size = 0;
    queue->capacity = initial_capacity;

    return queue;
}

void pq_destroy(PriorityQueueT* queue){

    if(queue == NULL){
        return;
    }

    free(queue->data);
    free(queue);
}