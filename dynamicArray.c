#include "dynamicArray.h"
#include <stdio.h>


DynamicArrayT* dynamic_array_create(size_t initial_capacity){

    DynamicArrayT* array = malloc(sizeof(DynamicArrayT));
    if(array == NULL){
        return NULL;
    }
    int* data = malloc(sizeof(int) * initial_capacity);
    if(data == NULL){
        free(array);
        return NULL;
    }


    array->size = 0;
    array->capacity = initial_capacity;
    array->data = data;

    return array;
}