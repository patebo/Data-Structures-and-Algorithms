#include <stdio.h>

#include "IntStack.h"

int main() {
  IntStack is = is_create();

  is_push(is, 3);
  is_push(is, 8);
  is_push(is, 5);
  is_pop(is);
  is_push(is, 8);

  // should now have on the stack: 3, 8, 8
  while (!is_empty(is)) {
    printf("Item: %d\n", is_peek(is));
    is_pop(is);
  }
  return 0;
}
