#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int* test = (int*)malloc(sizeof(int));
  test[0] = 5;
  int pid;
  if (pid = fork() == 0) {
	printf("Child heap: %i\n", test[0]);
  }
  else {
	printf("Parent heap: %i\n", test[0]);
  }
}
