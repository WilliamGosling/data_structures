#include <stdio.h>

typedef struct Node{
    char* key;
    void* value;
    struct Node* next;
}NodeT;

typedef struct Hashmap{
    NodeT** buckets;
    size_t capacity;
    size_t count;
}HashmapT;

typedef struct HashMapIterator{
    HashmapT* map;
    size_t bucket_index;
    NodeT* current_node;
}HashMapIterator;

unsigned long hash(const char* key);
HashmapT* hashmap_create(size_t initial_capacity);
void hashmap_set(HashmapT* map, const char* key, void* value);
void* hashmap_get(HashmapT* map, const char* key);
void hashmap_delete(HashmapT* map, const char* key);
void hashmap_destroy(HashmapT* map);
HashMapIterator* hashmap_iterator_create(HashmapT* map);
NodeT* hashmap_iterate_next(HashMapIterator* iterator);