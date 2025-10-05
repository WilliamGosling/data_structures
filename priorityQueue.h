#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

typedef struct PriorityQueue{
    PQ_ItemT* items;
    size_t size;
    size_t capacity;
} PriorityQueueT;

typedef struct PQ_Item{
    int priority;
    void* data;
}PQ_ItemT;

// Creates a priority queue and returns a pointer to it
// Returns a pointer to a PriorityQueueT struct, NULL if memory allocation failed
PriorityQueueT* pq_create(size_t initial_capacity);

// Destroys a priority queue
// Returns 0 on success, -1 if parsed a NULL "queue"
int pq_destroy(PriorityQueueT* queue);

// Adds an item onto the priority queue and sorts it into the correct priority order
// Returns 0 on success, -1 if parsed a NULL "queue" or memory allocation failed
int pq_enqueue(PriorityQueueT* queue, int priority, void* data);

// Removes the root item and then resorts the queue into a sorted priority order
// The root item data is assigned to the parsed "out_value"
// Returns 0 on success, -1 if any parsed values are NULL or out of index
int pq_dequeue(PriorityQueueT* queue, void** out_value);

#endif