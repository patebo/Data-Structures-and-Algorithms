#ifndef _UTILS_H
#define _UTILS_H

// in: a pointer to an array of n integers
// out: -
// side effects: the array is filled with random integers
void random_junk(int *a, int n);


// in: -
// out: the current time (since some fixed moment in the past) in seconds
float current_time();

// in: a pointer to an array of n integers
// side effect: prints an error message and quits the program if the array
//              is not sorted.
void test_sorted(int* a, int n);


void print_array(int* a, int n);

#endif
