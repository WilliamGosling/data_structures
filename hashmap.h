#include <stdio.h>

typedef struct Node{
    char* key;
    void* value;
    struct Node* next;
}NodeT;

typedef struct Hashmap{
    Node** buckets;
    size_t capacity;
    size_t count;
}HashmapT;

unsigned long hash(const char* key);