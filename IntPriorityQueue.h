#ifndef _INTPRIORITYQUEUE_H
#define _INTPRIORITYQUEUE_H

// Define struct IntPriorityQueueData in your answer.
typedef struct IntPriorityQueueData* IPQ;

// out: an empty IPQ.
IPQ ipq_create();

// in: an IPQ Q.
// side effect: free all the memory that's associated with IQ.
void ipq_destroy(IPQ Q);

// in: an IPQ Q, a number n to add to the queue, and a priority.
// side effect: n is stored in the queue datastructure.
void ipq_enqueue(IPQ Q, int n, float priority);

// in: an IPQ Q
// out: the number of items in the priority queue.
int ipq_size(IPQ Q);

// in: an IPQ Q
// side effect: the lowest priority item is removed from the queue
// out: the lowest priority item
int ipq_dequeue(IPQ Q);

#endif
