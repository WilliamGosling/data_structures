#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdio.h>

typedef struct DynamicArray{
    void* data;
    size_t size;
    size_t capacity;
    size_t element_size;
}DynamicArrayT;

// Creates a dynamic array
// Returns pointer to the array, NULL if memory allocation fails
DynamicArrayT* dynamic_array_create(size_t initial_capacity, size_t element_size);

// Destroys a dynamic array
// Returns 0 on success, -1 if parsed a NULL argument
int dynamic_array_destroy(DynamicArrayT* array);

// Adds a new index at the end of the array
// Returns 0 on success, -1 if the growing array fails
int dynamic_array_append(DynamicArrayT* array, void* data);

// Fetches the data from a given index
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_get(const DynamicArrayT* array, size_t index, void* out_value);

// Sets the data at a given index
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_set(DynamicArrayT* array, size_t index, void* value);

// Removes the element at the given index
// Returns 0 on success, -1 if the index is out of bounds
int dynamic_array_remove(DynamicArrayT* array, size_t index);

// Shrinks the array
// Returns 0 on success, -1 if shrinking array fails
int dynamic_array_shrink(DynamicArrayT* array, int new_capacity);

// Fetches the element at the given index
// Returns a pointer to the element, NULL if given a NULL argument or the index is out of bounds
void* dynamic_array_get_element_ptr(DynamicArrayT* array, size_t index);

// Fetches the element at the given index
// Returns a read-only pointer to the element, NULL if given a NULL argument or the index is out of bounds
const void* dynamic_array_get_element_ptr_const(const DynamicArrayT* array, size_t index);

#endif