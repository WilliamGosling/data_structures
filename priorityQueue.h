#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

typedef struct PriorityQueue{
    int* data;
    size_t size;
    size_t capacity;
} PriorityQueueT; 

// Returns a pointer to a PriorityQueueT struct, NULL if memory allocation failed
PriorityQueueT* pq_create(size_t initial_capacity);

void pq_destroy(PriorityQueueT* queue);

#endif