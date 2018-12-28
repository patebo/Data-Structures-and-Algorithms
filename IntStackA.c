#include <stdlib.h>
#include <stdio.h>

#include "IntStack.h"

struct IntStackData {
  int* data;
  int size;
  int alloc;
};



// out: an empty IntStack
IntStack is_create() {
  IntStack box = (IntStack)malloc(sizeof(struct IntStackData));
  box->data = (int *)malloc(100*sizeof(int));
  box->size = 0;   // same as (*box).size = 0;
  box->alloc = 100;
  return box;
}

// in: a IntStack is
// side effect: memory used by is is freed
void is_destroy(IntStack is) {
  free(is->data);
  free(is);
}

// in: a IntStack is and an int n
// side effect: the int n is added on top of the stack
void is_push(IntStack is, int n) {
  if (is->size >= is->alloc) {
    // out of space! reallocate
    int new_alloc = 2*is->alloc;
    int* new_data = (int*)malloc(new_alloc*sizeof(int));
    for (int i=0; i<is->size; i++) {
      new_data[i] = is->data[i];
    }
    free(is->data);
    is->data = new_data;
    is->alloc = new_alloc;
  }
  is->data[is->size] = n;
  is->size++;
}

// in: a IntStack is
// out: 1 if the stack is empty, 0 otherwise
int is_empty(IntStack is) {
  return is->size == 0;
}


// in: a IntStack is
// out: the int that is at the top of the stack
int is_peek(IntStack is) {
  if (is_empty(is)) {
    printf("is_peek: attempt to peek in an empty stack!\n");
    exit(1);
  }
  return is->data[is->size-1];
}

// in: a IntStack is
// side effect: the topmost item is removed (and memory is freed)
void is_pop(IntStack is) {
  if (is_empty(is)) {
    printf("is_pop: attempt to pop an empty stack!\n");
    exit(1);
  }
  is->size--;
}
