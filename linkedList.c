#include "linkedList.h"

LinkedListT* list_create(){

    LinkedListT* list = malloc(sizeof(LinkedListT));
    if(list == NULL){
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int list_destroy(LinkedListT* list){

    if(list == NULL){
        return -1;
    }

    NodeT* current = list->head;

    while(current != NULL){
        NodeT* temp = current->next;
        free(current);
        current = temp;
    }
    free(list);
    return 0;
}

int list_destroy_all_data(LinkedListT* list, void(*free_func)(void*)){

    if(list == NULL){
        return -1;
    }

    NodeT* current = list->head;
    while(current != NULL){
        NodeT* temp = current->next;
        if(free_func != NULL){
            free_func(current->data);
        }
        free(current);
        current = temp;
    }
    free(list);
    return 0;
}

int list_push_front(LinkedListT* list, void* data){

    if(list == NULL){
        return -1;
    }
    

    NodeT* node = malloc(sizeof(NodeT));
    if(node == NULL){
        return -1;
    }

    node->data = data;
    node->prev = NULL;
    node->next = list->head;

    if(list->head != NULL){
        list->head->prev = node;
    } else{
        list->tail = node;
    }

    list->head = node;
    list->size++;
    return 0;
}

int list_push_back(LinkedListT* list, void* data){

    if(list == NULL){
        return -1;
    }

    NodeT* node = malloc(sizeof(NodeT));
    if(node == NULL){
        return -1;
    }

    node->data = data;
    node->next = NULL;
    node->prev = list->tail;

    if(list->tail != NULL){
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
    list->size++;
    return 0;
}

int list_pop_front(LinkedListT* list){

    if(list == NULL || list->head == NULL){
        return -1;
    }

    NodeT* popped_node = list->head;
    list->head = list->head->next;

    if(list->head != NULL){
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(popped_node);
    list->size--;
    return 0;
}

int list_pop_back(LinkedListT* list){

    if(list == NULL || list->tail == NULL){
        return -1;
    }

    NodeT* popped_node = list->tail;
    list->tail = list->tail->prev;
    
    if(list->tail != NULL){
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(popped_node);
    list->size--;
    return 0;
}

int list_print(LinkedListT* list, void (*print_func)(void*)){

    if(list == NULL){
        return -1;
    }
    if(list->head == NULL){
        printf("Empty List\n");
        return -2;
    }

    NodeT* current = list->head;
    printf("Head -> ");

    while(current != NULL){
        print_func(current->data);
        if(current->next != NULL){
            printf(" <=> ");
        }
        current = current->next;
    }
    printf(" <- Tail\n");
    printf("List size: %zu\n", list->size);
    return 0;
}