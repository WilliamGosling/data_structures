#include "dynamicArray.h"
#include <stdio.h>

DynamicArrayT* dynamic_array_create(size_t initial_capacity, size_t element_size){

    DynamicArrayT* array = malloc(sizeof(DynamicArrayT));
    if(array == NULL){
        return NULL;
    }

    if(initial_capacity == 0){
        array->data = NULL;
    } else {
        array->data = malloc(element_size * initial_capacity);
        if(array->data == NULL){
            free(array);
            return NULL;
        }
    }

    array->size = 0;
    array->capacity = initial_capacity;
    array->element_size = element_size;

    return array;
}

int dynamic_array_destroy(DynamicArrayT* array){

    if(array == NULL){
        return -1;
    }
    free(array->data);
    free(array);
    return 0;
}

int dynamic_array_append(DynamicArrayT* array, void* data){

    if(array->size == array->capacity){
        size_t new_capacity = array->capacity == 0 ? 1 : array->capacity * 2;
        void* temp = realloc(array->data, array->element_size * new_capacity);
        if(temp == NULL){
            return -1;
        }
        array->data = temp;
        array->capacity = new_capacity;
    }

    int used_memory = (array->element_size * array->size);
    char* free_block = (char*)array->data + used_memory;

    memcpy(free_block,data, array->element_size);
    array->size++;
    return 0;
}

int dynamic_array_get(const DynamicArrayT* array, size_t index, void* out_value){

    if(array == NULL || out_value == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    char* index_memory = (char*)array->data + (index * array->element_size);
    memcpy(out_value, index_memory, array->element_size);

    return 0;
}

int dynamic_array_set(DynamicArrayT* array, size_t index, void* data){

    if(array == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    char* index_memory = (char*)array->data + (index * array->element_size);
    memcpy(index_memory, data, array->element_size);
    return 0;
}

int dynamic_array_remove(DynamicArrayT* array, size_t index){

    if(array == NULL){
        return -1;
    }
    if(index >= array->size){
        return -1;
    }

    char* index_memory = (char*)array->data + (index * array->element_size);
    char* moving_memory = (char*)array->data + ((index + 1) * array->element_size);
    memmove(index_memory, moving_memory, array->element_size * ((array->size - 1) - index));
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

    void* new_array = realloc(array->data,array->element_size * new_capacity);
    if(new_array == NULL){
        return -1;
    }
    array->data = new_array;
    array->capacity = new_capacity;
    return 0;
}

void* dynamic_array_get_element_ptr(DynamicArrayT* array, size_t index){
    
    if(array == NULL || index >= array->size){
        return NULL;
    }
    char* index_memory = (char*)array->data + (index * array->element_size);

    return index_memory;
}

const void* dynamic_array_get_ptr_const(const DynamicArrayT* array, size_t index){

    if(array == NULL || index >= array->size){
        return NULL;
    }
    const char* index_memory = (const char*)array->data + (index * array->element_size);

    return index_memory;
}