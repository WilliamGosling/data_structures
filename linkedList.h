#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct Node{
    void* data;
    struct Node* next;
    struct Node* prev;
}NodeT;

typedef struct LinkedList{
    NodeT* head;
    NodeT* tail;
    size_t size;
}LinkedListT;

// Creates a doubly linked list
// Returns a pointer to a list on success, NULL if memory allocation failed
LinkedListT* list_create();
// Destroys the list
// Returns 0 on success, -1 if parsed a NULL argument
int list_destroy(LinkedListT* list);
// Destroys the list and data using the provided function
// Returns 0 on success, -1 if parsed a NULL argument
int list_destroy_all_data(LinkedListT* list, void(*free_func)(void*));
// Pushes a new node onto the front of the list
// Returns 0 on success, -1 if parsed a NULL argument or a memory allocation failure
int list_push_front(LinkedListT* list, void* data);
// Pushes a new node onto the end of the list
// Returns 0 on success, -1 if parsed a NULL argument or a memory allocation failure
int list_push_back(LinkedListT* list, void* data);
// Pops the first node off of the list
// Returns 0 on success, -1 if parsed a NULL argument or the list is empty
int list_pop_front(LinkedListT* list);
// Pops the last node off of the list
// Returns 0 on success, -1 if parsed a NULL argument or the list is empty
int list_pop_back(LinkedListT* list);
// Prints the list contents using the function provided
// Returns 0 on success, -1 if parsed a NULL argument, -2 if the list is empty
int list_print(LinkedListT* list, void (*print_func)(void*));
#endif