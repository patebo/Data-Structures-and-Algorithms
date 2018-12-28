#ifndef _INTQUEUE_H
#define _INTQUEUE_H

// Your assignment is to develop an implementation of a Queue<int>,
// using EITHER an array data structure, OR a linked list data structure.

// You can freely borrow code from IntStackA.c and IntStackLL.c, which
// were developed during the lecture. However you'll have to think about
// how to adapt the code to make sure that it supports the operations
// specified below.
//
// In particular, items stored in the queue using "iq_enqueue" should
// come out in a first in, first out (FIFO) order.

// Define struct IntQueue in your answer.
typedef struct IntQueue* IntQueue;

// out: an empty IntQueue.
IntQueue iq_create();

// in: an IntQueue IQ.
// side effect: free all the memory that's associated with IQ.
void iq_destroy(IntQueue IQ);

// in: an IntQueue IQ and a number n to add to the queue.
// side effect: n is stored in the queue datastructure.
void iq_enqueue(IntQueue IQ, int n);

// in: an IntQueue IQ
// out: 1 if the queue is empty, and 0 if it's not.
int iq_empty(IntQueue IQ);

// in: an IntQueue IQ
// out: the oldest, first inserted value that's still in the queue.
int iq_peek(IntQueue IQ);

// in: an IntQueue IQ
// side effect: the oldest, first inserted item is removed from the queue.
void iq_dequeue(IntQueue IQ);

#endif
