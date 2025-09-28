#include <stdio.h>

typedef struct DynamicArray{
    int* data;
    size_t size;
    size_t capacity;
}DynamicArrayT;

DynamicArrayT* dynamic_array_create(size_t initial_capacity);