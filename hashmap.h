#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <pthread.h>

typedef struct Node{
    char* key;
    void* value;
    struct Node* next;
}NodeT;

typedef struct Hashmap{
    NodeT** buckets;
    size_t capacity;
    size_t count;
    pthread_mutex_t mutex;
}HashmapT;

typedef struct HashMapIterator{
    HashmapT* map;
    size_t bucket_index;
    NodeT* current_node;
}HashMapIterator;

// Creates a hashmap
// Returns a pointer to a hashmap, NULL if memory allocation failed
HashmapT* hashmap_create(size_t initial_capacity);

// Sets the data at a given key value
// Returns 0 on success, -1 if memory allocation or assignment failed
int hashmap_set(HashmapT* map, const char* key, void* value);

// Fetches the data at the given key
// Returns a pointer to the key value, NULL if the node doesn't exist
void* hashmap_get(HashmapT* map, const char* key);

// Deletes a key-value pair at a given key
// Returns 0 on success, -1 if node is not found 
int hashmap_delete(HashmapT* map, const char* key);

// Destroys a hashmap
// Returns 0 on success, -1 if parsed a NULL hashmap
int hashmap_destroy(HashmapT* map);

// Creates a hashmap iterator
// Returns a pointer to a hashmap iterator, NULL if memory allocation fails
HashMapIterator* hashmap_iterator_create(HashmapT* map);

// Iterator updates to the next node
// Returns a pointer to the node, NULL if bucket_index goes out of bound
NodeT* hashmap_iterate_next(HashMapIterator* iterator);

// Destroys the iterator
// Returns 0 on success, -1 if parsed a NULL iterator
int hashmap_iterator_destroy(HashMapIterator* iterator);

// Resizes the hashmap to the given capacity
// Returns 0 on success, -1 if memory allocation failed
int hashmap_resize(HashmapT* map, size_t new_capacity);

// Checks whether the hashmap has index at a given key
// Returns 1 if the value exists in the hashmap, else returns 0 
int hashmap_has_key(HashmapT* map, const char* key);

// Frees all the nodes in the hashmap
// Returns 0 on success, -1 if parsed a NULL hashmap
int hashmap_clear(HashmapT* map);

// Creates an array of all the keys in the hashmap
// Returns a pointer to an array, NULL if memory allocation failed
// User must free returned array
char** hashmap_keys(HashmapT* map);

#endif