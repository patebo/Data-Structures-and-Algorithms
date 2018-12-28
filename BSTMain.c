#include <stdio.h>
#include "BST.h"


void test_rebalance() {
  printf("\n\nTesting BST rebalancing:\n");
  BST T = bst_create();
  for (int i=1; i<=20; i++) {
    bst_insert(T, i);
  }
  bst_print(T);
  printf("Size: %d, height: %d\n", bst_size(T), bst_height(T));

  printf("\nAfter rebalancing:\n");
  bst_rebalance(T);
  bst_print(T);
  printf("Size: %d, height: %d\n", bst_size(T), bst_height(T));
  bst_destroy(T);
}

void test_sort() {
  printf("\n\nTesting BST sorting:\n");
  int keys[] = { 30, 53, 34, 8, 17, 58, 93, 17, 48, 3, 12 };
  int n = sizeof(keys)/sizeof(int);
  printf("Calling bst sort\n");
  bst_sort(keys, n);
  printf("bst sort complete, n is %d\n", n);
  for (int i=0; i<n; i++) {
    printf("  %d\n", keys[i]);
  }
}

int main() {
  test_sort();
  test_rebalance();
  return 0;
}
