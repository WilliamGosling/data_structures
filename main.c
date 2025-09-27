#include "hashmap.h"
#include <stdio.h>

int main(){

    int initial_capacity = 20;
    char* key = "40";
    void* value = "Test";

    HashmapT* map = hashmap_create(initial_capacity);
    hashmap_set(map,key, value);
    char* output = (char*)hashmap_get(map, key);
    printf("Value of %s is %s\n",key, output);
    hashmap_delete(map, key);
    hashmap_destroy(map);
    return 0;
}