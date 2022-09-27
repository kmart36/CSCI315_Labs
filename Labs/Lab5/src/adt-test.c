#include <stdlib.h>
#include <stdio.h>
#include "circular-list.h" 

void print_circular_list(struct circular_list *l) {
  printf("circular list: ");
  for (int i = 0; i < l->size; i++) {
    printf("%f ", l->buffer[i]);
  }
  printf("\n");
}

int main (int argc, char *argv[]) {
  item test_i;
  struct circular_list circ_list;
  
  circular_list_create(&circ_list, 4);
  
  printf("Remove with nothing in it: %d\n", circular_list_remove(&circ_list, &test_i));

  circular_list_insert(&circ_list, 2);
  circular_list_insert(&circ_list, 3);
  circular_list_insert(&circ_list, 4);
  
  print_circular_list(&circ_list);

  circular_list_remove(&circ_list, &test_i);
  printf("Removed item: %f\n", test_i);
  circular_list_remove(&circ_list, &test_i);
  printf("Removed item: %f\n", test_i);

  print_circular_list(&circ_list);
  
  circular_list_insert(&circ_list, 5);
  circular_list_insert(&circ_list, 6);
  circular_list_insert(&circ_list, 7);
  
  printf("Insert too many items: %d\n", circular_list_insert(&circ_list, 8));

  print_circular_list(&circ_list);
}
