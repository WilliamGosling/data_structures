#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

    NodeT** buckets = calloc(initial_capacity, sizeof(struct Node*));
    assert(buckets);
    hashmap->buckets = buckets;
    return hashmap;
}

void hashmap_set(HashmapT* map, const char* key, void* value){

    unsigned long index = hash(key);
    NodeT* node = map->buckets[index];

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

void* hashmap_get(HashmapT* map, const char* key){

    unsigned long index = hash(key);
    NodeT* node = map->buckets[index];
    if(node == NULL){
        return NULL;
    }

    while (node != NULL){
        if(strcmp(node->key, key) == 0){
            return node->value;
        }
    node = node->next;
    }

    return  NULL;
}

void hashmap_delete(HashmapT* map, const char* key){

    unsigned long index = hash(key);
    NodeT* node = map->buckets[index];
    NodeT* prev = NULL; 

    if(node == NULL){
        return;
    }

    while(node != NULL){
        if(strcmp(node->key, key) == 0){
            if(prev == NULL){
                map->buckets[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node->key);
            free(node);
            map->count--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void hashmap_destroy(HashmapT* map){
    if(map == NULL){
        return;
    }

    for(long unsigned int i = 0;i < map->capacity;i++){
        NodeT* node = map->buckets[i];
        while(node != NULL){
            NodeT* next_node = node->next;
            free(node->key);
            free(node);
            node = next_node;
        }
    }
    free(map->buckets);
    free(map);
}

HashMapIterator* hashmap_iterator_create(HashmapT* map){

    HashMapIterator* iterator = malloc(sizeof(HashMapIterator));
    iterator->map = map;
    iterator->bucket_index = 0;
    iterator->current_node = map->buckets[0];
    return iterator;
}

NodeT* hashmap_iterate_next(HashMapIterator* iterator){

    while(iterator->current_node == NULL){
        if(iterator->bucket_index >= iterator->map->capacity){
            return NULL;
        }
        iterator->current_node = iterator->map->buckets[iterator->bucket_index];
        iterator->bucket_index++;
    }
    NodeT* return_node = iterator->current_node;
    iterator->current_node = return_node->next;

    return return_node;
}

void hashmap_iterator_destroy(HashMapIterator* iterator){

    if(iterator == NULL){
        return;
    }

    free(iterator);
}