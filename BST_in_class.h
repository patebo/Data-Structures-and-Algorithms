#ifndef _BST_H
#define _BST_H

typedef struct BSTData*      BST;
typedef struct TreeNodeData* TreeNode;


// show how to implement
BST bst_create();
void bst_destroy(BST T) ;
void bst_print(BST T);

// write together
void bst_insert(BST T, int key);
TreeNode bst_lookup(BST T, int key);
void bst_delete(BST T, int key);

// homework
int bst_size(BST T);
int bst_height(BST T);
int bst_in_order(BST T, int* a);
void bst_sort(int* a, int n);
void bst_create_from_sorted(int* a, int n);
void bst_rebalance(BST T);

#endif
