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

unsigned long hash(const char* key);
HashmapT* hashmap_create(size_t initial_capacity);
int hashmap_set(HashmapT* map, const char* key, void* value);
void* hashmap_get(HashmapT* map, const char* key);
void hashmap_delete(HashmapT* map, const char* key);
void hashmap_destroy(HashmapT* map);
HashMapIterator* hashmap_iterator_create(HashmapT* map);
NodeT* hashmap_iterate_next(HashMapIterator* iterator);
void hashmap_iterator_destroy(HashMapIterator* iterator);
static void hashmap_resize(HashmapT* map, size_t new_capacity);
int hashmap_has_key(HashmapT* map, const char* key);