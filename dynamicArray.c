#include "dynamicArray.h"
#include <stdio.h>

DynamicArrayT* dynamic_array_create(size_t initial_capacity){

    DynamicArrayT* array = malloc(sizeof(DynamicArrayT));
    if(array == NULL){
        return NULL;
    }

    if(initial_capacity == 0){
        array->data = NULL;
    } else {
        array->data = malloc(sizeof(int) * initial_capacity);
        if(array->data == NULL){
            free(array);
            return NULL;
        }
    }

    array->size = 0;
    array->capacity = initial_capacity;

    return array;
}

void dynamic_array_destroy(DynamicArrayT* array){

    if(array == NULL){
        return;
    }
    free(array->data);
    free(array);
}

int dynamic_array_append(DynamicArrayT* array, int value){

    if(array->size == array->capacity){
        size_t new_capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        int* temp = realloc(array->data,sizeof(int) * (array->capacity * 2));
        if(temp == NULL){
            return -1;
        }
        array->data = temp;
        array->capacity = new_capacity;
    }
    array->data[array->size] = value;
    array->size++;
    return 0;
}

int dynamic_array_get(DynamicArrayT* array, size_t index, int* out_value){

    if(array == NULL || out_value == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    *out_value = array->data[index];
    return 0;
}

int dynamic_array_set(DynamicArrayT* array, size_t index, int value){

    if(array == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    array->data[index] = value;
    return 0;
}

int dynamic_array_remove(DynamicArrayT* array, size_t index){

    if(array == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    for(size_t i = index;i < array->size - 1;i++){
        array->data[i] = array->data[i + 1];
    }
    array->size--;


    if(array->capacity > 16 && array->size <= array->capacity / 4){
        size_t new_capacity = array->capacity / 2;
        if(dynamic_array_shrink(array, new_capacity) == -1){
            return -1;
        }
    }
    return 0;
}

int dynamic_array_shrink(DynamicArrayT* array, int new_capacity){

    if(array == NULL){
        return -1;
    }

    int* new_array = realloc(array->data,sizeof(int) * new_capacity);
    if(new_array == NULL){
        return -1;
    }
    array->data = new_array;
    array->capacity = new_capacity;
    return 0;
}