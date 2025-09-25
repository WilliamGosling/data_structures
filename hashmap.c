#include "hashmap.h"

size_t capcity_mod;

unsigned long hash(const char* key){

    unsigned long hash = 5381;
    int c;
    while((c = *key++))
        hash = ((hash << 5) + hash) + c;


    return hash % capcity_mod;
}

HashmapT* hashmap_create(size_t initial_capacity){

    HashmapT* hashmap = malloc(sizeof(struct Hashmap));
    assert(hashmap);

    hashmap->capacity = initial_capacity;
    hashmap->count = 0;
    capcity_mod = initial_capacity;

    NodeT** buckets = calloc(sizeof(struct Node*) * initial_capacity);
    assert(buckets);
    hashmap->buckets = buckets;
    return hashmap;
}

void hashmap_set(HashmapT* map, const char* key, void* value){

    unsigned long index = hash(key);
    NodeT* node = map->buckets[index];
    assert(node);
    checking = 1;

    while(node != NULL){
        if(strcmp(node->key,key) == 0){
            node->value = value;
            return;
            }
        node = node->next;
    }

    NodeT* new_node = malloc(sizeof(NodeT));

    if(new_node == NULL){
        return;
    }
    
    new_node->key = strdup(key);
    if(new_node->key == NULL){
        free(new_node);
        return;
    }

    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
    map->count++;
}