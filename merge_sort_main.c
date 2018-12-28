#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"


List cons(int item, List lst) {
  List new_node = (List)malloc(sizeof(struct ListNode));
  if (new_node==NULL) { printf("Failed to allocate memory\n"); exit(1); }
  new_node->item = item;
  new_node->next = lst;
  return new_node;
}

void destroy_list(List lst) {
  if (lst!=NULL) {
    destroy_list(lst->next);
    free(lst);
  }
}

void print_list(List lst) {
  printf("[");
  int first = 1;
  while (lst!=NULL) {
    if (first) { first = 0; } else { printf(","); }
    printf("%d", lst->item);
    lst = lst->next;
  }
  printf("]");
}


// Add more tests if you want to!
void test_length() {
  printf("Testing length\n");
  List lst = cons(3, cons(8, cons(4, NULL)));
  printf("Length of ");
  print_list(lst);
  printf(" is %d\n", list_length(lst));
  destroy_list(lst);

  lst = NULL;
  printf("Length of ");
  print_list(lst);
  printf(" is %d.\n\n", list_length(lst));
}

void test_split() {
  printf("Testing split\n");
  List lst = NULL;
  //List lst = cons(4, NULL);
  //List lst = cons(3, cons(8, cons(4, NULL)));
  //List lst = cons(12, cons(13, cons(2, cons(7, cons(13, cons(32, NULL))))));
  print_list(lst);
  printf(" got split into ");
  List tail = split_list(lst);
  print_list(lst);
  printf(" and ");
  print_list(tail);
  printf(".\n\n");
  destroy_list(lst);
  destroy_list(tail);
}

void test_merge() {
  printf("Testing merge\n");
  //List lst1 = cons(3, cons(8, cons(9, NULL)));
  //List lst1 = cons(7, NULL);
  List lst1 = cons(7, cons(7, cons(9, cons(12, NULL))));
  List lst2 = cons(5, cons(6, cons(8, cons(11, cons(15, NULL)))));
  //List lst2 = NULL;
  printf("merge of ");
  print_list(lst1);
  printf(" and ");
  print_list(lst2);
  printf(" yields ");
  List res = merge_lists(lst1, lst2);
  print_list(res);
  printf(".\n\n");
  destroy_list(res);
}

void test_merge_sort() {
  printf("Testing merge_sort\n");
  List lst = cons(3, cons(8, cons(4, cons(1, cons(6, cons(4, NULL))))));
  //List lst = cons(11, cons(23, cons(4, cons(9, cons(5, cons(15, NULL))))));
  printf("merge_sort of ");
  print_list(lst);
  printf(" yields ");
  lst = merge_sort(lst);
  print_list(lst);
  printf(".\n\n");
  destroy_list(lst);
}

int main() {
  test_length();
  test_split();
  test_merge();
  test_merge_sort();
  return 0;
}
