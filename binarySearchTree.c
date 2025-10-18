#include "binarySearchTree.h"
#include <stdlib.h>

// Helper function declarations
static BSTNode* create_node(int value);
static void destroy_nodes_bst(BSTNode* node);

BSTree* bst_create(){
    
    BSTree* tree = malloc(sizeof(BSTree));
    if(tree == NULL){
        return NULL;
    }
  
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

int bst_destroy(BSTree* tree){

    if(tree == NULL){
        return -1;
    }

    destroy_nodes_bst(tree->root);

    free(tree);
    return 0;
}

int bst_insert(BSTree* tree, int value){

    if(tree == NULL){
        return -1;
    }

    if(tree->root == NULL){
        BSTNode* node = create_node(value);
        if(node == NULL){
            return -1;
        }
        tree->size++;
        tree->root = node;
        return 0;
    }
    BSTNode* current = tree->root;
    while(1){
        if(value <= current->data){
            if(current->left == NULL){
                current->left = create_node(value);
                tree->size++;
                return 0;
            }
            current = current->left;
        }else if(value > current->data){
            if(current->right == NULL){
                current->right = create_node(value);
                tree->size++;
                return 0;
            }
            current = current->right;
        } 
    }
}

int bst_search(const BSTree* tree, int value){

    if(tree == NULL || tree->root == NULL){
        return -1;
    }
    
    BSTNode* current = tree->root;

    while(current != NULL){
        if(current->data == value){
            return 0;
        }
        if(value < current->data){
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return -1;
}

int bst_remove(BSTree* tree, int value){

    if(tree == NULL || tree->root == NULL){
        return -1;
    }

    BSTNode* parent = NULL;
    BSTNode* current = tree->root;
    
    while(current != NULL && current->data != value){
        parent = current;
        if(value < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    if(current == NULL){
        return 0;
    }

    if(current->left == NULL && current->right == NULL){
        if(parent == NULL){
            tree->root = NULL;
        }else if(parent->left == current){
            parent->left = NULL;
        } else{
            parent->right = NULL;
        }
        free(current);
        tree->size--;
        return 0;
    }
    else if(current->left == NULL || current->right == NULL){
        BSTNode* child = (current->left != NULL) ? current->left : current->right;
        if(parent == NULL){
            tree->root = child;
        } else if(parent->left == current){
              parent->left = child;
        } else{
                parent->right = child;
            }
        free(current);
        tree->size--;
        return 0;
    } else {
        BSTNode* successor_parent = current;
        BSTNode* successor = current->right;

        while(successor->left != NULL){
            successor_parent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        if(successor_parent->left == successor){
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        free(successor);
        tree->size--;
        return 0;
    }
    return -1;
}

// Private helper functions

static void destroy_nodes_bst(BSTNode* node){

    if(node == NULL){
        return;
    }

    destroy_nodes_bst(node->left);
    destroy_nodes_bst(node->right);

    free(node);
}

static BSTNode* create_node(int value){

    BSTNode* node = malloc(sizeof(BSTNode));
    if(node == NULL){
        return NULL;
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}