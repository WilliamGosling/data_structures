#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MINIMUM_CAPACITY 5

static unsigned long hash(const char* key){

    unsigned long hash = 5381;
    int c;
    while((c = *key++))
        hash = ((hash << 5) + hash) + c;


    return hash;
}

HashmapT* hashmap_create(size_t initial_capacity){

    HashmapT* hashmap = malloc(sizeof(struct Hashmap));
    if(hashmap == NULL){
        return NULL;
    }

    hashmap->capacity = initial_capacity;
    hashmap->count = 0;
    pthread_mutex_init(&hashmap->mutex, NULL);

    NodeT** buckets = calloc(initial_capacity, sizeof(struct Node*));
    if(buckets == NULL){
        return NULL;
    }
    hashmap->buckets = buckets;
    return hashmap;
}

int hashmap_set(HashmapT* map, const char* key, void* value){

    pthread_mutex_lock(&map->mutex);
    unsigned long index = hash(key) % map->capacity;
    NodeT* node = map->buckets[index];

    while(node != NULL){
        if(strcmp(node->key,key) == 0){
            node->value = value;
            pthread_mutex_unlock(&map->mutex);
            return 0;
            }
        node = node->next;
    }

    NodeT* new_node = malloc(sizeof(NodeT));

    if(new_node == NULL){
        pthread_mutex_unlock(&map->mutex);
        return -1;
    }
    
    new_node->key = strdup(key);
    if(new_node->key == NULL){
        free(new_node);
        pthread_mutex_unlock(&map->mutex);
        return -1;
    }

    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
    map->count++;
    if((float)map->count / map->capacity > 0.75){
        hashmap_resize(map,map->capacity * 2);
    }
    pthread_mutex_unlock(&map->mutex);
    return 0;
}

void* hashmap_get(HashmapT* map, const char* key){

    pthread_mutex_lock(&map->mutex);
    unsigned long index = hash(key) % map->capacity;
    NodeT* node = map->buckets[index];
    if(node == NULL){
        pthread_mutex_unlock(&map->mutex);
        return NULL;
    }

    while (node != NULL){
        if(strcmp(node->key, key) == 0){
            pthread_mutex_unlock(&map->mutex);
            return node->value;
        }
    node = node->next;
    }
    pthread_mutex_unlock(&map->mutex);
    return  NULL;
}

int hashmap_delete(HashmapT* map, const char* key){

    pthread_mutex_lock(&map->mutex);
    unsigned long index = hash(key) % map->capacity;
    NodeT* node = map->buckets[index];
    NodeT* prev = NULL; 

    if(node == NULL){
        pthread_mutex_unlock(&map->mutex);
        return -1;
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
            if(((float)map->count / map->capacity < 0.25) && (map->capacity > MINIMUM_CAPACITY)){
                hashmap_resize(map, map->capacity / 2);
            }
            pthread_mutex_unlock(&map->mutex);
            return -1;
        }
        prev = node;
        node = node->next;
    }
    pthread_mutex_unlock(&map->mutex);
    return 0;
}

int hashmap_destroy(HashmapT* map){
    if(map == NULL){
        return -1;
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
    pthread_mutex_destroy(&map->mutex);
    free(map->buckets);
    free(map);
    return 0;
}

HashMapIterator* hashmap_iterator_create(HashmapT* map){

    HashMapIterator* iterator = malloc(sizeof(HashMapIterator));
    if(iterator == NULL){
        return NULL;
    }
    pthread_mutex_lock(&map->mutex);
    iterator->map = map;
    iterator->bucket_index = 0;
    iterator->current_node = map->buckets[0];
    pthread_mutex_unlock(&map->mutex);
    return iterator;
}

NodeT* hashmap_iterate_next(HashMapIterator* iterator){

    pthread_mutex_lock(&iterator->map->mutex);
    while(iterator->current_node == NULL){
        if(iterator->bucket_index >= iterator->map->capacity){
            pthread_mutex_unlock(&iterator->map->mutex);
            return NULL;
        }
        iterator->current_node = iterator->map->buckets[iterator->bucket_index];
        iterator->bucket_index++;
    }
    NodeT* return_node = iterator->current_node;
    iterator->current_node = return_node->next;

    pthread_mutex_unlock(&iterator->map->mutex);
    return return_node;
}

int hashmap_iterator_destroy(HashMapIterator* iterator){

    if(iterator == NULL){
        return -1;
    }
    free(iterator);
    return 0;
}

int hashmap_resize(HashmapT* map, size_t new_capacity){

    NodeT** new_buckets = calloc(new_capacity, sizeof(struct Node*));
    if(new_buckets == NULL){
        return -1;
    }
    NodeT** old_buckets = map->buckets;
    size_t old_capacity = map->capacity;
    map->buckets = new_buckets;
    map->capacity = new_capacity;

    for(long unsigned int i = 0; i < old_capacity;i++){
        NodeT* current_node = old_buckets[i];
        while(current_node != NULL){
            NodeT* next_node = current_node->next;
            size_t new_index = hash(current_node->key) % map->capacity;
            current_node->next = map->buckets[new_index];
            map->buckets[new_index] = current_node;
            current_node = next_node;
        }
    }
    free(old_buckets);
    return 0;
}

int hashmap_has_key(HashmapT* map, const char* key){

   if(hashmap_get(map, key) == NULL){
        return 0;
    }
    return 1;
}

int hashmap_clear(HashmapT* map){

    if(map == NULL){
        return -1;
    }

    pthread_mutex_lock(&map->mutex);
    for(unsigned long int i = 0;i < map->capacity;i++){
        NodeT* node = map->buckets[i];
        while(node != NULL){
            NodeT* next_node = node->next;
            free(node->key);
            free(node);
            node = next_node;
        }
        map->buckets[i] = NULL;
    }
    map->count = 0;
    pthread_mutex_unlock(&map->mutex);
    return 0;
}

char** hashmap_keys(HashmapT* map){

    pthread_mutex_lock(&map->mutex);

    char** key_array = malloc(sizeof(char*) * (map->count + 1));
    if(key_array == NULL){
        pthread_mutex_unlock(&map->mutex);
        return NULL;
    }

    HashMapIterator* iterator = hashmap_iterator_create(map);
    size_t i = 0;
    NodeT* current_node;

    while((current_node = hashmap_iterate_next(iterator)) != NULL){
        key_array[i] = current_node->key;
        i++;
        }
    key_array[i] = NULL;
    hashmap_iterator_destroy(iterator);
    pthread_mutex_unlock(&map->mutex);
    return key_array;
}
