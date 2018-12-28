#include <stdio.h>
#include <stdlib.h>

#include "IntStack.h"

struct ListNode {
  int item;
  struct ListNode* next;
};

// typedef struct IntStackData* IntStack;
struct IntStackData {
  struct ListNode* head;
};


// out: an empty IntStack
IntStack is_create() {
  IntStack is;
  is = (struct IntStackData*)malloc(sizeof(struct IntStackData));
  if (is==NULL) {
    printf("allocation failed :-(\n");
    exit(1);
  }
  is->head = NULL;
  return is;
}

// in: a IntStack is
// side effect: memory used by is is freed
void is_destroy(IntStack is) {
  while (!is_empty(is)) {
    is_pop(is);
  }
  free(is);
}

// in: a IntStack is
// out: the int that is at the top of the stack
int is_peek(IntStack is) {
  if (is_empty(is)) {
    printf("It's empty, can't peek\n");
    exit(1);
  }
  return is->head->item;
}

// in: a IntStack is
// side effect: the topmost item is removed (and memory is freed)
void is_pop(IntStack is) {
  if (is_empty(is)) {
    printf("It's empty, can't pop\n");
    exit(1);
  }
  struct ListNode* second_item = is->head->next;
  free(is->head);
  is->head = second_item;
}

// in: a IntStack is and an int n
// side effect: the int n is added on top of the stack
void is_push(IntStack is, int n) {
  struct ListNode* new_node;
  new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
  if (new_node==NULL) {
    printf("allocation failed :-(\n");
    exit(1);
  }
  new_node->next = is->head;
  new_node->item = n;
  is->head = new_node;
}

// in: a IntStack is
// out: 1 if the stack is empty, 0 otherwise
int is_empty(IntStack is) {
  return is->head==NULL;
}
