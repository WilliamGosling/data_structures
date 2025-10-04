#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stddef.h>

typedef struct BSTNode{
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BSTree{
    BSTNode* root;
    size_t size;
} BSTree;

// Returns an empty binary search tree 
BSTree* bst_create();

void bst_destroy(BSTree* tree);
// Returns 0 on success, -1 if NULL parameter parsed or failed memory allocation
int bst_insert(BSTree* tree, int value);
// Returns 1 if value found, 0 if failed to find value or if NULL parameter parsed
int bst_search(BSTree* tree, int value);
// Returns 0 if value is removed, -1 if NULL parameter parsed or failed to remove value
int bst_remove(BSTree* tree, int value);

#endif