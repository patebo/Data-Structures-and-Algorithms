#include <stdio.h>
#include <stdlib.h>

#include "IntPriorityQueue.h"

struct IPQNode {
  int item;
  float priority;
};

struct IntPriorityQueueData {
  struct IPQNode* array;
  int alloc;
  int size;
};

// out: an empty IPQ.
IPQ ipq_create() {
  IPQ Q = (IPQ)malloc(sizeof(struct IntPriorityQueueData));
  if (Q==NULL) { printf("Allocation error\n"); exit(1); }
  Q->size = 0;
  Q->alloc = 10000;
  Q->array = (struct IPQNode*)malloc(Q->alloc*sizeof(struct IPQNode));
  if (Q->array==NULL) { printf("Allocation error\n"); exit(1); }
  return Q;
}

// in: an IPQ Q.
// side effect: free all the memory that's associated with IQ.
void ipq_destroy(IPQ Q) {
  free(Q->array);
  free(Q);
}

void percolate_up(IPQ Q, int i) {
  struct IPQNode percolating = Q->array[i];
  while (i>0) {
    int parent = (i-1)/2;
    if (Q->array[parent].priority <= percolating.priority) {
      break;
    }
    Q->array[i] = Q->array[parent];
    i = parent;
  }
  Q->array[i] = percolating;
}

void percolate_down(IPQ Q, int i) {
  struct IPQNode percolating = Q->array[i];
  while (1) {
    int left_child = i+i+1;
    if (left_child >= Q->size) { break; }
    int smallest_child = left_child;

    int right_child = left_child + 1;
    if (right_child < Q->size &&
        Q->array[right_child].priority < Q->array[left_child].priority) {
      smallest_child = right_child;
    }

    if (Q->array[smallest_child].priority >= percolating.priority) {
      break;
    }

    Q->array[i] = Q->array[smallest_child];
    i = smallest_child;
  }
  Q->array[i] = percolating;
}


// in: an IPQ Q, an int item to add to the queue, and its priority.
// side effect: n is stored in the queue datastructure.
void ipq_enqueue(IPQ Q, int item, float priority) {
  if (Q->size == Q->alloc) { printf("ipq_enqueue: out of space\n"); exit(1); }
  int i = Q->size;
  Q->size++;
  Q->array[i].item     = item;
  Q->array[i].priority = priority;
  percolate_up(Q, i);
}

// in: an IPQ Q
// out: the number of items in the priority queue.
int ipq_size(IPQ Q) { return Q->size; }

// in: an IPQ Q
// side effect: the lowest priority item is removed from the queue
// out: the lowest priority item
int ipq_dequeue(IPQ Q) {
  if (Q->size==0) { printf("Trying to dequeue from an empty queue.\n"); exit(1); }
  int item = Q->array[0].item;
  Q->size--;
  Q->array[0] = Q->array[Q->size];
  percolate_down(Q, 0);
  return item;
}
