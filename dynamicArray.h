#include <stdio.h>

typedef struct DynamicArray{
    int* data;
    size_t size;
    size_t capacity;
}DynamicArrayT;

DynamicArrayT* dynamic_array_create(size_t initial_capacity);
void dynamic_array_destroy(DynamicArrayT* array);
int dynamic_array_append(DynamicArrayT* array, int value);
int dynamic_array_get(DynamicArrayT* array, size_t index, int* out_value);
int dynamic_array_set(DynamicArrayT* array, size_t index, int value);
int dynamic_array_remove(DynamicArrayT* array, size_t index);