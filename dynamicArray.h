#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdio.h>

typedef struct DynamicArray{
    void* data;
    size_t size;
    size_t capacity;
    size_t element_size;
}DynamicArrayT;

// Returns pointer to the array, NULL if memory allocation fails
DynamicArrayT* dynamic_array_create(size_t initial_capacity);

void dynamic_array_destroy(DynamicArrayT* array);
// Returns 0 on success, -1 if the growing array fails
int dynamic_array_append(DynamicArrayT* array, int value);
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_get(DynamicArrayT* array, size_t index, int* out_value);
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_set(DynamicArrayT* array, size_t index, int value);
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_remove(DynamicArrayT* array, size_t index);
// Returns 0 on success, -1 if shrinking array fails
int dynamic_array_shrink(DynamicArrayT* array, int new_capacity);

#endif