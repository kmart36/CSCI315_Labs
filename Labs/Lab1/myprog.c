#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int parent_count = 0;
  int child_count1, child_count2 = 0;
  int f1 = fork();
  if (f1 == 0) {
	while (child_count1 > -1) {
	  child_count1++;
	  printf("child1: %d\n", child_count1);
	}
  }
  else {
	int f2 = fork();
	if (f2 == 0) {
	  while (child_count2 > -1) {
		child_count2++;
		printf("child2: %d\n", child_count2);
	  }
	}
	else {
	  while (parent_count > -1) {
		parent_count++;
		printf("parent: %d\n", parent_count);
	  }
	}
  }
}
