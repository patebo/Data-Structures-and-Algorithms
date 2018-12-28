#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

// ------- the following are homework, to be implemented in BST.c ------------

// *** First, to get some practice, write functions to work out the size and
// *** the height of the tree.
// *** Be careful to think about boundary conditions, such as the empty tree.

// in: a BST T
// out: the number of keys in the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int how_many_keys(TreeNode n) {
  if (n==NULL) {return 0; }
  else {
    return 1 + how_many_keys(n->left) + how_many_keys(n->right);
  }
}

int bst_size(BST T) {
  return how_many_keys(T->root);
}

// in: a BST T
// out: the height of the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int max(int a, int b) {
  if (a>=b) {return a; }
  else {return b; }
}

int height_rec(TreeNode n) {
  if (n==NULL) {return -1; }
  else {
    return 1 + max(height_rec(n->left),height_rec(n->right));
  }
}

int bst_height(BST T) {
  return height_rec(T->root);
}


// *** We will also need a function to traverse the tree in order, and dump the
// *** result in an array. You'll need to think about *where* in the array
// *** each key needs to be stored.
int traverse_in_order(TreeNode n, int* a, int pos) {
  // assume n is the root of a subtree (or perhaps NULL)
  // a is an array where I'm supposed to store all the stuff
  // pos is the index in the array where I should start putting stuff
  // work out size of left subtree
  if (n->left != NULL) {
    pos = traverse_in_order(n->left, a, pos);
  }
    a[pos++]= n->key;
  if (n->right != NULL) {
    pos = traverse_in_order(n->right, a, pos);
  }
    //printf("%d\n",pos);
    return pos;
  }
// in: a BST T and a pointer to an array a of ints with enough space to hold
//     all keys in the tree. (There are bst_size(T) of them.)
// side effect: all keys in the tree are stored in a in ascending order, using
//     an in-order traversal of the tree.
// out: the number of keys that were stored in the array, that is, the same
//     as bst_size(T).
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_in_order(BST T, int* a) {
  if (T->root==NULL) {return -1; }
  a = (int*)malloc(bst_size(T));
  if (a==NULL) { printf("allocation error\n"); exit(1); }
  //traverse_in_order(T->root,a,how_many_keys((T->root)->left));
  int s = traverse_in_order(T->root,a,0);
  bst_destroy(T);
  return s;
}

// *** You can use the bst code you've written so far to sort an array
// *** of ints! The resulting sorting algorithm is pretty efficient
// *** on most data.

// in: an array a with n ints, in no particular order
// side effect: the items in the array are sorted using a BST in the process.
void bst_sort(int* a, int n) {
  BST Tr = bst_create();
  for (int i=0; i<n; i++) {
    bst_insert(Tr,a[i]);
  }
  //traverse_in_order(Tr->root,a,how_many_keys((Tr->root)->left));
  traverse_in_order(Tr->root,a,0);
  bst_destroy(Tr);
}

// *** To balance a tree we need to be able to go the other way around, and
// *** construct a tree directly from a sorted array. Use the function
// *** bst_make_new_node.

// in: an array a with n ints, in sorted order
// out: a *perfectly balanced* BST containing the items in a.
// hint: use a recursive helper function that takes a TreeNode instead of a BST
//void balanced_BST_create(TreeNode node, int* a, int s, int n) {
  //if (s>n) {return; }
  //int mid = s+(n-s)/2;
  //node = make_new_node(a[mid]);
  //balanced_BST_create(node->left, a, s, mid-1);
  //balanced_BST_create(node->right, a, mid+1, n);
//}
TreeNode make_a_new_node(int key) {
  TreeNode n = (TreeNode)malloc(sizeof(struct TreeNodeData));
  if (n==NULL) { printf("allocation error\n"); exit(1); }
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  return n;
}

TreeNode balanced_BST_create(int* a, int s, int n) {
  if (s>n) {return NULL; }
  int mid = s+(n-s)/2;
  BST T = bst_create();
  T->root = make_a_new_node(a[mid]);
  T->root->left = balanced_BST_create(a, s, mid-1);
  T->root->right = balanced_BST_create(a, mid+1, n);
  return T->root;
}

BST bst_create_from_sorted(int* a, int n) {
  BST T = bst_create();
  T->root = balanced_BST_create(a, 0, n-1);
  return T;
}

// *** We can combine the functions we wrote to do a full tree rebalancing.

// in: a BST T
// side effect: the BST is made *perfectly balanced*
void free_all_nodes(TreeNode n) {
  if (n==NULL) { return; }
  free_all_nodes(n->left);
  free_all_nodes(n->right);
  free(n);
}

void bst_rebalance(BST T) {
  int sz = bst_size(T);
  int storing_array[sz];
  traverse_in_order(T->root, storing_array,0);
  free_all_nodes(T->root);
  T->root = bst_create_from_sorted(storing_array, sz)->root;
}
