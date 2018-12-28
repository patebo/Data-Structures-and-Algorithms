#include <stdio.h>
#include <stdlib.h>

#include "avl.h"


struct AVLTreeData {
  TreeNode root;
};

struct TreeNodeData {
  int key;
  TreeNode left;
  TreeNode right;
  int height;
};

// A utility function to get maximum of two integers
int max(int a, int b) {
  if (a>b) { return a; }
  return b;
}

// A utility function to get the height of the tree
int height(TreeNode n) {
  if (n == NULL) {
    return -1;
  }
  return n->height;
}

int balance(TreeNode n) {
  if (n == NULL) { return 0; }
  return height(n->left) - height(n->right);
}


AVLTree avl_create() {
  AVLTree T = (AVLTree)malloc(sizeof(struct AVLTreeData));
  if (T==NULL) { printf("Allocation error\n"); exit(1); }
  T->root = NULL;
  return T;
}

void destroy_rec(TreeNode n) {
  if (n!=NULL) {
    destroy_rec(n->left);
    destroy_rec(n->right);
    free(n);
  }
}

void avl_destroy(AVLTree T) {
  destroy_rec(T->root);
  free(T);
}

void print_rec(TreeNode n, int level) {
  if (n!=NULL) {
    print_rec(n->right, level+1);
    for (int i=0; i<level; i++) {
      printf("      ");
    }
    printf(" %02d(%d)\n", n->key, n->height);
    print_rec(n->left, level+1);
  }
}

void avl_print(AVLTree T) {
  print_rec(T->root, 0);
}

TreeNode new_node(int key) {
  TreeNode n = (TreeNode)malloc(sizeof(struct TreeNodeData));
  if (n==NULL) { printf("Allocation error\n"); exit(1); }
  n->key   = key;
  n->left   = NULL;
  n->right  = NULL;
  n->height = 0;  // new node is initially added at leaf
  return n;
}

TreeNode right_rotate(TreeNode y) {
  TreeNode x = y->left;
  TreeNode T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  // Return new root
  return x;
}

TreeNode left_rotate(TreeNode x) {
  TreeNode y = x->right;
  TreeNode T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  //  Update heights
  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  // Return new root
  return y;
}

// Ensure that the subtree rooted at n is balanced, by backtracking over
// the path from the root to the node with the given key.
TreeNode restore_balance_rec(TreeNode n, int key) {
  if (n==NULL) {
    return n;
  } else if (key < n->key) {
    n->left = restore_balance_rec(n->left, key);
  } else if (key > n->key) {
    n->right = restore_balance_rec(n->right, key);
  }

  // 2. Update height of this ancestor node */
  n->height = 1 + max(height(n->left),
                      height(n->right));

  // 3. Get the balance factor of this ancestor
  //    node to check whether this node became unbalanced
  int b = balance(n);

  // If this node becomes unbalanced, then
  // there are 4 cases

  // Left Left Case
  if (b > 1 && balance(n->left)>=0) {
    return right_rotate(n);
  }

  // Left Right Case
  if (b > 1 && balance(n->left) < 0) {
    n->left =  left_rotate(n->left);
    return right_rotate(n);
  }

  // Right Right Case
  if (b < -1 && balance(n->right) <= 0) {
    return left_rotate(n);
  }

  // Right Left Case
  if (b < -1 && balance(n->right)>0) {
    n->right = right_rotate(n->right);
    return left_rotate(n);
  }

  // return the (unchanged) node pointer
  return n;
}


void avl_insert(AVLTree T, int key) {
  TreeNode* n_p = &T->root;
  while (*n_p!=NULL) {
    if (key < (*n_p)->key) {
      n_p = &(*n_p)->left;
    } else if (key > (*n_p)->key) {
      n_p = &(*n_p)->right;
    } else {
      // Key was already in the tree: don't modify tree
      return;
    }
  }
  *n_p = new_node(key);
  T->root = restore_balance_rec(T->root, key);
}

void avl_delete(AVLTree T, int key) {

  // 1. Find the node.
  TreeNode* n_p = &T->root;
  while ((*n_p)!=NULL && key!=(*n_p)->key) {
    if (key < (*n_p)->key) { n_p = &((*n_p)->left);  }
    else                   { n_p = &((*n_p)->right); }
  }
  TreeNode n = *n_p;
  if (n==NULL) { return; } // not found.

  // 2. Handle case where the node has zero or one children.

  if (n->left==NULL) {
    *n_p = n->right;
  } else if (n->right == NULL) {
    *n_p = n->left;
  } else {

    // 3. If the node has two children, then
    //    (a) find the rightmost node in its left subtree

    TreeNode* c_p = &n->left;
    while ((*c_p)->right!=NULL) {
      c_p = &(*c_p)->right;
    }

    //    (b) move c to n's position in tree
    TreeNode c = *c_p;
    *c_p = NULL;                    // unlink c
    *n_p = c;                       // attach in place of n
    c->left = n->left;  // copy children
    c->right = n->right;
  }

  // 4. Finally, free the space used by the deleted node and rebalance.
  free(n);
  T->root = restore_balance_rec(T->root, key);
}
