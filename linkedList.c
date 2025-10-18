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

int list_print(const LinkedListT* list, void (*print_func)(void*)){

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

int list_is_empty(const LinkedListT* list){
    if(list == NULL){
        return -1;
    }
    return list->size == 0;
}

void* list_pop_front_data(LinkedListT* list){
    if(list == NULL || list->head == NULL){
        return NULL;
    }
    void* data = list->head->data;
    list_pop_front(list);
    return data;
}

void* list_pop_back_data(LinkedListT* list){
    if(list == NULL || list->tail == NULL){
        return NULL;
    }
    void* data = list->tail->data;
    list_pop_back(list);
    return data;
}

int list_insert_at(LinkedListT* list, size_t index, void* data){
    if(list == NULL || index > list->size){
        return -1;
    }
    if(index == 0){
        return list_push_front(list, data);
    }
    if(index == list->size){
        return list_push_back(list, data);
    }

    NodeT* current;
    if(index < list->size / 2){
        current = list->head;
        for(size_t i = 0;i < index;i++){
            current = current->next;
        }
    } else {
        for(size_t i = list->size - 1;i > index;i--){
            current = current->prev;
        }
    }
    
    NodeT* node = malloc(sizeof(NodeT));
    node->data = data;
    node->next = current;
    node->prev = current->prev;
    current->prev->next = node;
    current->prev = node;
    list->size++;
    return 0;
}

int list_remove_at(LinkedListT* list, size_t index){
    if(list == NULL || index > list->size){
        return -1;
    }
    if(index == 0){
        return list_pop_front(list);
    }
    if(index == list->size){
        return list_pop_back(list);
    }

    NodeT* current;
    if(index < list->size / 2){
        current = list->head;
        for(size_t i = 0;i < index;i++){
            current = current->next;
        }
    } else {
        for(size_t i = list->size - 1;i > index;i--){
            current = current->prev;
        }
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    list->size--;
    return 0;
}

void* list_get(const LinkedListT* list, size_t index){
    if(list == NULL || index >= list->size){
        return NULL;
    }

    NodeT* current;
    if(index < list->size /2){
        current = list->head;
        for(size_t i = 0;i < index;i++){
            current = current->next;
        }
    } else {
        current = list->tail;
        for(size_t i = list->size - 1;i > index;i--){
            current = current->prev;
        }
    }
    return current->data;
}

void* list_get_front(const LinkedListT* list){
    if(list == NULL || list->head == NULL){
        return NULL;
    }
    return list->head->data;
}

void* list_get_back(const LinkedListT* list){
    if(list == NULL || list->tail == NULL){
        return NULL;
    }
    return list->tail->data;
}

size_t list_size(const LinkedListT* list){
    return list == NULL ? -1 : list->size;
}

int list_find(const LinkedListT* list, void* data, int (*compare_func)(void*, void*)){
    if(list == NULL || compare_func == NULL){
        return -1;
    }
    NodeT* current = list->head;
    int index = 0;
    while(current != NULL){
        if(compare_func(current->data, data) == 0){
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int list_contains(const LinkedListT* list, void* data, int (*compare_func)(void*, void*)){
    return list_find(list, data, compare_func) != -1;
}

int list_clear(LinkedListT* list, void(*free_func)(void*)){
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

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return 0;
}