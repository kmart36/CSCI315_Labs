#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "dnode.h"
#include "dlist.h"
#include "allocator.h"

void frag_eval(int alg, unsigned int seed, int req) {
  srandom(seed);
  allocator_init(10240);

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
	
	if (s >= 500 && s <= 700) {
	  d = rand() % insert;
	  deallocate(alloc[d]);
	  insert--;
	}
	r++;
  }
  double avg = average_frag();
  printf("%f\n", avg);
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
	printf("Usage: ./analysis [samples] [requests]\n");
	exit(1);
  }
  int samples = atoi(argv[1]);
  int req = atoi(argv[2]);
  unsigned int seed = 50;
  int s;
  
  s = 0;
  printf("----- first-fit data -----\n");
  while (s < samples) {
	frag_eval(0, seed, req);
	s++;
	seed++;
  }
  
  s = 0;
  seed = 50;
  printf("----- best-fit data -----\n");
  while (s < samples) {
	frag_eval(1, seed, req);
	s++;
	seed++;
  }
  
  s = 0;
  seed = 50;
  printf("----- worst-fit data -----\n");
  while (s < samples) {
	frag_eval(2, seed, req);
	s++;
	seed++;
  }
}
