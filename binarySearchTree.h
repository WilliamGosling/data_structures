#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdlib.h>

typedef struct BSTNode{

    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BSTree{

    BSTNode* root;
    size_t size;
} BSTree;


BSTree* bst_create();
void bst_destroy(BSTree* tree);
int bst_insert(BSTree* tree, int value);

#endif