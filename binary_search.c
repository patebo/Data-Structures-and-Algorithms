#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"
#include "utils.h"

// in: a pointer to a SORTED array of n ints
//     an int to search for
// out: an index of the searched item, or -1 if it isn't there
int binary_search(int* a, int n, int item) {
  int lo = 0;
  int hi = n-1;
  while (lo<=hi) {
    // invariant: the item is either not in the array, or
    //            it is in a[lo], ..., a[hi].
    //            (If lo>hi, the range is empty, so the search is terminated)
    int mid = (lo+hi)/2; // calculate midpoint, rounding down. (Could round up)
    if (item < a[mid]) {
      // either the item is not in the array, or it is in a[lo], ... ,a[mid-1]
      hi = mid-1; // since mid<=hi, this must decrement hi
    } else if (item > a[mid]) {
      // either the item is not in the array, or it is in a[mid+1], ..., a[hi]
      lo = mid+1; // since mid>=lo, this must increment lo
    } else {
      // item == a[mid], we've found an index
      return mid;
    }
  }
  return -1;
}


int main() {
  int n = 20;
  int a[n];
  srand(time(NULL));
  random_junk(a, n);
  int item = a[0];
  printf("unsorted: "); print_array(a, n);
  sort(a, n);
  printf("sorted:   "); print_array(a, n);
  test_sorted(a, n);
  printf("binary_search for item: %d returned index %d\n",
         item, binary_search(a, n, item));
  printf("binary_search for item 23402384 returned index %d\n",
         binary_search(a, n, 23402384));
  return 0;
}
