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

unsigned long hash(const char* key);
HashmapT* hashmap_create(size_t initial_capacity);
void hashmap_set(HashmapT* map, const char* key, void* value);
void* hashmap_get(HashmapT* map, const char* key);
void hashmap_delete(HashmapT* map, const char* key);
void hashmap_destroy(HashmapT* map);