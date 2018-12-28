#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "searchery.h"

// in: a pointer to an array of n integers
// out: -
// side effects: the array is filled with random integers
void random_junk(int *a, int n) {
  for (int i=0; i<n; i++) {
    a[i] = rand();
  }
}

void shuffle(int* a, int n) {
  for (int i=1; i<n; i++) {
    int ix = rand()%(i+1);
    int tmp=a[i];
    a[i]=a[ix];
    a[ix] = tmp;
  }
}


void print_array(int* a, int n) {
  printf("[");
  for (int i=0; i<n; i++) {
    if (i>0) { printf(", "); }
    printf("%d", a[i]);
  }
  printf("]\n");
}

void test_q_O1() { printf("test_q_O1: your answer was: %d\n", q_O1()); }
void test_q_O2() { printf("test_q_O2: your answer was: %d\n", q_O2()); }

void test_linear_search_count() {
  int a[] = { 3, 10, -5, 4, 7 };
  int cmp;
  int key;
  int ix;

  printf("\ntest_linear_search_count:\n");
  printf("a = "); print_array(a, 5);

  cmp = 0;
  key = -5;
  ix = linear_search_count(a, 5, key, &cmp);
  printf("Finding %d: index=%d, cmp=%d\n", key, ix, cmp);

  cmp = 0;
  key = 100;
  ix = linear_search_count(a, 5, key, &cmp);
  printf("Finding %d: index=%d, cmp=%d\n", key, ix, cmp);
}

void test_move_to_front() {
  int a[] = { 3, 10, -5, 4, 7 };
  printf("\ntest_move_to_front:\n");
  printf("a = "); print_array(a, 5);
  move_to_front(a, 2);
  printf("After move_to_front(a,2): ");
  print_array(a, 5);
}

void test_searches() {
  int n = 1000;
  int a[n], b[n], c[n];
  int cmp_a;
  int cmp_b;

  printf("test_searches:\n");
  random_junk(a, n);
  for (int i=0; i<n; i++) { b[i] = a[i]; }

  // test both functions with a uniform access pattern
  cmp_a = 0;
  cmp_b = 0;
  for (int i=0; i<1000; i++) {
    int key = a[rand()%n];
    int ix_a = linear_search_count   (a, n, key, &cmp_a);
    int ix_b = linear_search_adaptive(b, n, key, &cmp_b);
    if (ix_a==-1 || a[ix_a]!=key) { printf("Error a: key not found during test\n"); }
    if (ix_b==-1 || b[ix_b]!=key) { printf("Error b: key not found during test\n"); }
  }
  printf("- Uniform access pattern: nonadaptive:cmp=%d adaptive:cmp=%d\n",
    cmp_a, cmp_b);

  for (int i=0; i<n; i++) { b[i] = a[i]; c[i] = a[i]; }
  shuffle(c, n);

  // test both functions with highly nonuniform access pattern
  cmp_a = 0;
  cmp_b = 0;
  for (int i=0; i<1000; i++) {
    int ix = 0;
    while (rand()%10!=0) { ix = (ix+1)%n; }
    int key = c[ix];
    int ix_a = linear_search_count(a, n, key, &cmp_a);
    int ix_b = linear_search_adaptive(b, n, key, &cmp_b);
    if (ix_a==-1 || a[ix_a]!=key) { printf("Error a: key not found during test\n"); }
    if (ix_b==-1 || b[ix_b]!=key) { printf("Error b: key not found during test\n"); }
  }
  printf("- Nonniform access pattern: nonadaptive:cmp=%d adaptive:cmp=%d\n",
    cmp_a, cmp_b);
}

int main() {
  srand(time(NULL));
  test_q_O1();
  test_q_O2();
  test_move_to_front();
  test_searches();
  return 0;
}
