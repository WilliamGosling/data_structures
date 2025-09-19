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