#include "binarySearchTree.h"


BSTree* bst_create(){
    
    BSTree* tree = malloc(sizeof(BSTree));
    if(tree == NULL){
        return NULL;
    }
  
    tree->root = NULL;
    tree->size = 0;

    return tree;
}

void bst_destroy(BSTree* tree){

    if(tree == NULL){
        return;
    }

    destroy_nodes_bst(tree->root);

    free(tree);
}

void destroy_nodes_bst(BSTNode* node){

    if(node == NULL){
        return;
    }

    destroy_nodes_bst(node->left);
    destroy_nodes_bst(node->right);

    free(node);
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

BSTNode* create_node(int value){

    BSTNode* node = malloc(sizeof(BSTNode));
    if(node == NULL){
        return NULL;
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}