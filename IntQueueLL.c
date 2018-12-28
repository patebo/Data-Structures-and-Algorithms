#include <stdlib.h>
#include <stdio.h>
#include "IntQueue.h"

// Define struct IntQueue in your answer.
typedef struct IntQueue* IntQueue;

struct IntQueue {
  struct ListNode* first;
  struct ListNode* last;
};

struct ListNode {
  int item;
  struct ListNode* next;
};

// out: an empty IntQueue.
IntQueue iq_create() {
  IntQueue IQ = (struct IntQueue*)malloc(sizeof(struct IntQueue));
  if (IQ==NULL) {
    printf("allocation failed\n");
    exit(1);
  }
  IQ->first = NULL;
  IQ->last = NULL;
  return IQ;
}

// in: an IntQueue IQ.
// side effect: free all the memory that's associated with IQ.
void iq_destroy(IntQueue IQ) {
  while (!iq_empty(IQ)) {
    iq_dequeue(IQ);
  }
  free(IQ);
}

// in: an IntQueue IQ and a number n to add to the queue.
// side effect: n is stored in the queue datastructure.
void iq_enqueue(IntQueue IQ, int n) {
  struct ListNode* new_node;
  new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
  if (new_node==NULL) {
    printf("allocation failed\n");
    exit(1);
  }
  new_node->item = n;
  new_node->next = NULL;
  if (iq_empty(IQ)) {
    IQ->first = new_node;
    IQ->last = new_node;
    return;
  }
  IQ->last->next = new_node;
  IQ->last = new_node;
}

// in: an IntQueue IQ
// out: 1 if the queue is empty, and 0 if it's not.
int iq_empty(IntQueue IQ) {
  return (IQ->first==NULL && IQ->last==NULL);
}

// in: an IntQueue IQ
// out: the oldest, first inserted value that's still in the queue.
int iq_peek(IntQueue IQ) {
  if (iq_empty(IQ)) {
    printf("It's empty, can't peek\n");
    exit(1);
  }
  return IQ->first->item;
}

// in: an IntQueue IQ
// side effect: the oldest, first inserted item is removed from the queue.
void iq_dequeue(IntQueue IQ) {
  if (iq_empty(IQ)) {
    printf("It's empty, can't dequeue\n");
    exit(1);
  }
  if (IQ->first == IQ->last) {
    IQ->last = IQ->last->next;
  }
  struct ListNode* second_item = IQ->first->next;
  free(IQ->first);
  IQ->first = second_item;
}
