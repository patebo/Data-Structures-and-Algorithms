#ifndef _BST_H
#define _BST_H

typedef struct BSTData*      BST;
typedef struct TreeNodeData* TreeNode;

// *** Create a program "bst.c" and implement all the functions that are
// *** not already implemented in BST_in_class.c.

// *** For convenience, the structure definitions have been moved from
// *** BST_in_class.c to here, so that they can be used in BST_balance.c as
// *** well.

struct BSTData {
  TreeNode root;
};

struct TreeNodeData {
  int key;
  TreeNode left;
  TreeNode right;
};

// ------ The following are defined in BST_in_class.c, NOT homework -----------

// in: a key
// out: a newly allocated TreeNode with the given key, and both children
//      set to NULL.
TreeNode bst_make_new_node(int key);

// out: an empty BST
BST bst_create();

// in: a BST T
// side effect: all memory associated with T is released
void bst_destroy(BST T) ;

// in: a BST T
// side effect: the tree is printed with the root at the left hand side.
void bst_print(BST T);

// in: a BST T and a key to insert
// side effect: the key is inserted in the tree such that the BST
//              property is preserved.
void bst_insert(BST T, int key);

// in: a BST T and a key to look up
// out: a TreeNode with the given key or NULL if it's not found.
TreeNode bst_lookup(BST T, int key);

// in: a BST T and a key to delete
// side effect: if the key appears in the tree, one node with that key
//              is deleted in such a way that the BST property is preserved.
void bst_delete(BST T, int key);

// ------- the following are homework, to be implemented in BST.c ------------

// *** First, to get some practice, write functions to work out the size and
// *** the height of the tree.
// *** Be careful to think about boundary conditions, such as the empty tree.

// in: a BST T
// out: the number of keys in the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_size(BST T);

// in: a BST T
// out: the height of the BST
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_height(BST T);


// *** We will also need a function to traverse the tree in order, and dump the
// *** result in an array. You'll need to think about *where* in the array
// *** each key needs to be stored.

// in: a BST T and a pointer to an array a of ints with enough space to hold
//     all keys in the tree. (There are bst_size(T) of them.)
// side effect: all keys in the tree are stored in a in ascending order, using
//     an in-order traversal of the tree.
// out: the number of keys that were stored in the array, that is, the same
//     as bst_size(T).
// hint: use a recursive helper function that takes a TreeNode instead of a BST
int bst_in_order(BST T, int* a);

// *** You can use the bst code you've written so far to sort an array
// *** of ints! The resulting sorting algorithm is pretty efficient
// *** on most data.

// in: an array a with n ints, in no particular order
// side effect: the items in the array are sorted using a BST in the process.
void bst_sort(int* a, int n);

// *** To balance a tree we need to be able to go the other way around, and
// *** construct a tree directly from a sorted array. Use the function
// *** bst_make_new_node.

// in: an array a with n ints, in sorted order
// out: a *perfectly balanced* BST containing the items in a.
// hint: use a recursive helper function that takes a TreeNode instead of a BST
BST bst_create_from_sorted(int* a, int n);


// *** We can combine the functions we wrote to do a full tree rebalancing.

// in: a BST T
// side effect: the BST is made *perfectly balanced*
void bst_rebalance(BST T);

#endif
