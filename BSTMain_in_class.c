#include <stdio.h>
#include "BST.h"

int main() {
  int keys[] = { 30, 53, 34, 8, 58, 93, 17, 48, 3, 12 };
  int n = sizeof(keys)/sizeof(int);

  BST T = bst_create();
  for (int i=0; i<12; i++) {
    bst_insert(T, i);
  }
  printf("\nTree with numbers from 0 to 11:\n");
  bst_print(T);
  int key_to_delete = 5;
  printf("\nDeleting %d, tree is now:\n", key_to_delete);
  bst_delete(T, key_to_delete);
  bst_print(T);
  bst_destroy(T);

  T = bst_create();
  for (int i=0; i<n; i++) {
    bst_insert(T, keys[i]);
  }
  bst_print(T);

  key_to_delete = keys[1];
  printf("\nDeleting %d, tree is now:\n", key_to_delete);
  bst_delete(T, key_to_delete);
  bst_print(T);
  bst_destroy(T);

  return 0;
}
