#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

// in: a pointer to an array of n integers
// out: -
// side effects: the array is filled with random integers
void random_junk(int *a, int n) {
  for (int i=0; i<n; i++) {
    a[i] = rand();
  }
}

// in: -
// out: the current time (since some fixed moment in the past) in milliseconds
float current_time() {
  return 1000*(float)clock()/CLOCKS_PER_SEC;
}

// in: a pointer to an array of n integers
// side effect: stops the program with an error if the array is not sorted
void test_sorted(int* a, int n) {
  for (int i=1; i<n; i++) {
    if (a[i-1]>a[i]) {
      printf("Array unsorted: a[%d]=%d > a[%d]=%d\n", i-1, a[i-1], i, a[i]);
      exit(1);
    }
  }
}

// in: a pointer to an array of n integers
// side effect: prints the array
void print_array(int* a, int n) {
  printf("[");
  for (int i=0; i<n; i++) {
    if (i>0) { printf(", "); }
    printf("%d", a[i]);
  }
  printf("]\n");
}
