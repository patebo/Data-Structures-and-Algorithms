#include "sort.h"



void percolate(int* a, int k) {
  int item = a[k];
  int j = k;
  while (j>0 && a[j-1] > item) {
    a[j] = a[j-1];
    j--;
  }
  a[j] = item;
}

// in: an int* pointing to an array of n integers
// out: -
// side effect: the integers in the array are permuted into sorted order
void sort(int* a, int n) {
  int i;
  for (i=1; i<n; i++) {
    percolate(a, i);
  }
}
