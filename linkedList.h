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
// Checks if the linked list is empty
// Returns 1 if the list is empty, 0 if it is not empty 
int list_is_empty(LinkedListT* list);
// Fetches the data from the front of the list & pops that element from the list
// Returns a pointer to the data, NULL if parsed a NULL argument or the list is empty
void* list_pop_front_data(LinkedListT* list);
// Fetches the data from the back of the list & pops that element from the list
// Returns a pointer to the data, NULL if parsed a NULL argument or the list is empty
void* list_pop_back_data(LinkedListT* list);
// Inserts a new element at the given index position
// Returns 0 on success, -1 if parsed a NULL argument or provided index is out of bounds 
int list_insert_at(LinkedListT* list, size_t index, void* data);
// Removes the element at the given index position
// Returns 0 on success, -1 if parsed a NULL argument or provided index is out of bounds
int list_remove_at(LinkedListT* list, size_t index);
// Fetches the data from a given index position
// Returns a pointer to the data, NULL if parsed a NULL argument or provided index is out of bounds 
void* list_get(LinkedListT* list, size_t index);
// Fetches the data from the front of the list
// Returns a pointer to the data, NULL if parsed a NULL argument or the list is empty
void* list_get_front(LinkedListT* list);
// Fetches the data from the back of the list
// Returns a pointer to the data, NULL if parsed a NULL argument or the list is empty
void* list_get_back(LinkedListT* list);
// Gets the size of the list
// Returns the size of the list, -1 if parsed a NULL argrument
size_t list_size(LinkedListT* list);
// Finds the index that data belongs to using the provided compare function
// Return index value, -1 if the data cannot be matched to an element or if parsed a NULL argument
int list_find(LinkedListT* list, void* data, int (*compare_func)(void*, void*));
// Checks whether the data is in the list
// Returns 1 if it is in the list, 0 if it is not in the list
int list_contains(LinkedListT* list, void* data, int (*compare_func)(void*, void*));
// Clears the list of all of its elements using the provided free function
// Returns 0 on success, -1 if parsed a NULL argument
int list_clear(LinkedListT* list, void(*free_func)(void*));
#endif