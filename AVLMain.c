#include <stdio.h>

#include "avl.h"

int main() {

  AVLTree T = avl_create();
  for (int i=0; i<20; i++) {
    avl_insert(T, i);
    printf("\n\nThe tree after inserting %d\n", i);
    avl_print(T);
  }

  for (int i=0; i<20; i++) {
    avl_delete(T, i);
    printf("\n\nThe tree after deleting %d\n", i);
    avl_print(T);
  }

  avl_destroy(T);

  return 0;
}
