#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

// show how to implement

struct BSTData {
  TreeNode root;
};

struct TreeNodeData {
  int key;
  TreeNode left;
  TreeNode right;
};

// create and return an empty BST
BST bst_create() {
  BST T = (BST)malloc(sizeof(struct BSTData));
  if (T==NULL) { printf("Allocation error\n"); exit(1); }
  T->root = NULL;
  return T;
}

void free_all_the_nodes(TreeNode n) {
  if (n==NULL) { return; }
  free_all_the_nodes(n->left);
  free_all_the_nodes(n->right);
  free(n);
}

void bst_destroy(BST T) {
  free_all_the_nodes(T->root);
}

void bst_print_rec(TreeNode n, int depth) {
  if (n==NULL) { return; }
  bst_print_rec(n->right, depth+1);

  for (int i=0; i<depth; i++) {
    printf("   ");
  }

  printf(" %02d\n", n->key);

  bst_print_rec(n->left, depth+1);
}

void bst_print(BST T) {
  bst_print_rec(T->root, 0);
}

// write together


TreeNode make_new_node(int key) {
  TreeNode n = (TreeNode)malloc(sizeof(struct TreeNodeData));
  if (n==NULL) { printf("allocation error\n"); exit(1); }
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  return n;
}

// n should not be NULL. It should point to an honest to god actual node.
void bst_insert_rec(TreeNode n, int key) {
  if (key < n->key) {
    if (n->left == NULL) {
      n->left = make_new_node(key);
    } else {
      bst_insert_rec(n->left, key);
    }
  } else {
    if (n->right == NULL) {
      n->right = make_new_node(key);
    } else {
      bst_insert_rec(n->right, key);
    }
  }
}

void bst_insert(BST T, int key) {
    if (T->root == NULL) {
      T->root = make_new_node(key);
      return;
    }
    bst_insert_rec(T->root, key);
}



// returns a pointer to a TreeNode with the given key, or NULL
// if the key is not found in the tree.
TreeNode* bst_lookup_pointer_pointer(BST T, int key) {
  TreeNode* where_am_i = &T->root;
  while (*where_am_i != NULL) {
    if ((*where_am_i)->key == key) { return where_am_i; }
    if (key < (*where_am_i)->key) {
      where_am_i = &((*where_am_i)->left);
    } else {
      where_am_i = &((*where_am_i)->right);
    }
  }
  return where_am_i;
}

TreeNode bst_lookup(BST T, int key) {
  return *bst_lookup_pointer_pointer(T, key);
}


void bst_delete(BST T, int key) {
  TreeNode* to_delete_p = bst_lookup_pointer_pointer(T, key);
  if (*to_delete_p == NULL) { return; }

  if ((*to_delete_p)->left == NULL && (*to_delete_p)->right == NULL) {
    // node has no children
    free(*to_delete_p);
    *to_delete_p = NULL;
    return;
  } else if ((*to_delete_p)->left == NULL) {
    // node has only a right child
    TreeNode to_delete = *to_delete_p;
    *to_delete_p = to_delete->right;
    free(to_delete);
  } else if ((*to_delete_p)->right == NULL) {
    // node has only a left child
    TreeNode to_delete = *to_delete_p;
    *to_delete_p = to_delete->left;
    free(to_delete);
  } else {
    // node has both children
    TreeNode* ls_rightmost_p = &((*to_delete_p)->left);
    while ((*ls_rightmost_p)->right != NULL) {
      ls_rightmost_p = &((*ls_rightmost_p)->right);
    }
    TreeNode ls_rightmost = *ls_rightmost_p;
    TreeNode to_delete = *to_delete_p;
    *ls_rightmost_p = ls_rightmost->left;
    ls_rightmost->left = to_delete->left;
    ls_rightmost->right = to_delete->right;
    *to_delete_p = ls_rightmost;
    free(to_delete);
  }
}
