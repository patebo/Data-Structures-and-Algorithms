#include <stdio.h>
#include <string.h>

void array_indexing() {
  int a[10];
  int i = 42;
  int j = -1;

  printf("The size of a is %lu\n", sizeof(a));

  a[3] = 5;
  printf("a[3]  is %d\n", a[3]);  // just set to 5!
  printf("a[4]  is %d\n", a[4]);  // uninitialised
  printf("a[-1] is %d\n", a[-1]); // index -1 out of range!
  printf("a[%d] is %d\n", j, a[j]);  // index -1 still out of range!
}

void array_initialisation() {
  int a[] = { 3, 4, 5 }; // can omit the size of the array!
  printf("The size of a is %lu\n", sizeof(a));
  for (int i=0; i<3; i++) {
    printf("a[%d] = %d\n", i, a[i]);
  }
}

int main() {
  printf("\n*** array_indexing\n");       array_indexing();
  printf("\n*** array_initialisation\n"); array_initialisation();
  return 0;
}
