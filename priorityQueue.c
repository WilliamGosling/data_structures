#include "priorityQueue.h"

PriorityQueueT* pq_create(size_t initial_capacity){

    PriorityQueueT* queue = malloc(sizeof(PriorityQueueT));
    if(queue == NULL){
        return NULL;
    }

    if(initial_capacity == 0){
        queue->items = NULL;
    } else {
        queue->items = malloc(sizeof(PQ_ItemT) * initial_capacity);
        if(queue->items == NULL){
            free(queue);
            return NULL;
        }
    }

    queue->size = 0;
    queue->capacity = initial_capacity;
    return queue;
}

int pq_destroy(PriorityQueueT* queue){

    if(queue == NULL){
        return -1;
    }

    free(queue->items);
    free(queue);
    return 0;
}

int pq_enqueue(PriorityQueueT* queue, int priority, void* data){

    if(queue == NULL){
        return -1;
    }
    if(queue->size == queue->capacity){
        size_t new_capacity = queue->capacity == 0 ? 1 : queue->capacity * 2;
        PQ_ItemT* temp = realloc(queue->items,sizeof(PQ_ItemT) * new_capacity);
        if(temp == NULL){
            return -1;
        }
        queue->items = temp;
        queue->capacity = new_capacity;
    }
    queue->items[queue->size].priority = priority;
    queue->items[queue->size].data = data;
    queue->size++;

    size_t current_index = queue->size - 1;

    while(current_index > 0){
        size_t parent_index = (current_index - 1) / 2;
        if(queue->items[current_index].priority > queue->items[parent_index].priority){
            PQ_ItemT temp = queue->items[current_index];
            queue->items[current_index] = queue->items[parent_index];
            queue->items[parent_index] = temp;
            current_index = parent_index;
        } else {
            break;
        }
    }
    return 0;
}

int pq_dequeue(PriorityQueueT* queue, void** out_value){

    if(queue == NULL || out_value == NULL || queue->size == 0){
        return -1;
    }

    *out_value = queue->items[0].data;
    queue->items[0] = queue->items[queue->size - 1];
    queue->size--;

    if(queue->size == 0){
        return 0;
    }

    size_t current_index = 0;

    while(1){
        size_t left_child_index = current_index*2 + 1;
        size_t right_child_index = current_index*2 + 2;
        size_t largest_index = current_index;

        if(left_child_index < queue->size && queue->items[left_child_index].priority > queue->items[largest_index].priority){
            largest_index = left_child_index;
        }
        if(right_child_index < queue->size && queue->items[right_child_index].priority > queue->items[largest_index].priority){
            largest_index = right_child_index;
        }

        if(largest_index == current_index){
            break;
        }

        PQ_ItemT temp = queue->items[current_index];
        queue->items[current_index] = queue->items[largest_index];
        queue->items[largest_index] = temp;
        current_index = largest_index;
    }

    return 0;
}