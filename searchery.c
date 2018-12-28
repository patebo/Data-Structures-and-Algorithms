#include "searchery.h"

int q_O1() { return 13; }

int q_O2() { return 25; }

int linear_search_count(int* a, int n, int key, int* cmp) {
  int i;
  for (i=0;i<n;i++) {
    *cmp = *cmp + 1;
    if (key == a[i]) {
      return i;
    }
  }
  return -1;
}

void move_to_front(int* a, int k) {
  int i;
  int j = a[k];
  for (i=k; i>0; i--) {
    a[i] = a[i-1];
  }
  a[0] = j;
}

int linear_search_adaptive(int* a, int n, int key, int* cmp) {
  int i;
  for (i=0;i<n;i++) {
    *cmp = *cmp + 1;
    if (key == a[i]) {
      move_to_front(a,i);
      return 0;
    }
  }
  return -1;
}
