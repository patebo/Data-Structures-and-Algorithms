#ifndef _INTSTACK_H
#define _INTSTACK_H

typedef struct IntStackData* IntStack;

// out: an empty IntStack
IntStack is_create();

// in: a IntStack is
// side effect: memory used by is is freed
void is_destroy(IntStack is);

// in: a IntStack is
// out: the int that is at the top of the stack
int is_peek(IntStack is);

// in: a IntStack is
// side effect: the topmost item is removed (and memory is freed)
void is_pop(IntStack is);

// in: a IntStack is and an int n
// side effect: the int n is added on top of the stack
void is_push(IntStack is, int n);

// in: a IntStack is
// out: 1 if the stack is empty, 0 otherwise
int is_empty(IntStack is);


#endif
