#include <stdio.h>

#include "IntQueue.h"

int main() {
  IntQueue IQ = iq_create();

  iq_enqueue(IQ, 3);
  iq_enqueue(IQ, 8);
  iq_enqueue(IQ, 5);
  iq_dequeue(IQ);
  iq_enqueue(IQ, 8);

  //should now have on the queue: 8, 5, 8
  while (!iq_empty(IQ)) {
    printf("Item: %d\n", iq_peek(IQ));
    iq_dequeue(IQ);
  }
  return 0;
}
