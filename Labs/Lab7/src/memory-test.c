#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"
#include "allocator.h"

int main(int argc, char *argv[]) {
  int test = allocator_init(-1);
  printf("Testing error case for allocator_init. Should return -1: %i\n", test);
  test = allocator_init(500);
  printf("Testing allocator_init with size 500.\n");
  print_lists();
  printf("------------------------------\n");
  printf("Allocating size 50 with first-fit.\n");
  void *ptr = allocate(0, 50);
  print_lists();
  printf("Allocating size 100 with first-fit.\n");
  void *ptr2 = allocate(0, 100);
  print_lists();
  printf("Deallocating size 100.\n");
  deallocate(ptr2);
  print_lists();
  printf("Dellocating size 50.\n");
  deallocate(ptr);
  print_lists();
  printf("Allocating size 90 with first-fit.\n");
  ptr = allocate(0, 90);
  print_lists();
  printf("------------------------------\n");
  printf("Allocating size 50 with best-fit.\n");
  ptr = allocate(1, 50);
  print_lists();
  printf("Allocating size 100 with best-fit.\n");
  ptr2 = allocate(1, 100);
  print_lists();
  printf("Deallocating size 50.\n");
  deallocate(ptr);
  print_lists();
  printf("Dellocating size 100.\n");
  deallocate(ptr2);
  print_lists();
  printf("Allocating size 40 with best-fit.\n");
  ptr = allocate(1, 40);
  print_lists();  
  printf("------------------------------\n");
  printf("Allocating size 10 with worst-fit.\n");
  ptr = allocate(2, 10);
  print_lists();
  printf("Allocating size 90 with worst-fit.\n");
  ptr2 = allocate(2, 90);
  print_lists(); 
  printf("------------------------------\n");
  void *test1 =(void *) 8;
  test = deallocate(test1);
  printf("Testing deallocate error with an incorrect address pointer. Should return -1: %i\n", test);
  ptr2 = allocate(2, 5000);
  printf("Testing allocate error with a size larger than total memory. Should return NULL (nil): %p\n", ptr2);  
}

