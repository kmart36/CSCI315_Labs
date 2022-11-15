#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"
#include "allocator.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
	printf("Usage: ./frag-eval [algorithm] [seed] [requests]\n");
	exit(1);
  }
  int alg = atoi(argv[1]);
  unsigned int seed = atoi(argv[2]);
  int req = atoi(argv[3]);

  srandom(seed);
  
  int test = allocator_init(10240);

  int r = 0;
  int insert = 0;
  int d = 0;
  void *p = NULL;
  void *alloc[req + 1];
  
  
  while (r < req) {
	int s = rand() % 1000 + 100;

	p = allocate(alg, s);
	alloc[r] = p;
	insert++;

	printf("Current RAM:----------------------------------------------\n");
	print_lists();
	printf("----------------------------------------------------------\n");
 
	if (s >= 500 && s <= 700) {
	  d = rand() % insert;
	  printf("deallocating...\n");
	  d = rand() % insert;
	  deallocate(alloc[d]);
	  insert--;
	}
	r++;
  }
  double avg = average_frag();
  printf("Average fragmentation: %f\n", avg);
}

