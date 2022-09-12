#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int counter = 0;
char alphabet = 'a';

void *char_print(void *tid) {
  int thread = (int)tid;
  int sum = 0;
  while (1) {
	if (thread == 0) {
	  printf("%d\n", counter);
	  counter++;
	  if (counter == 10) {
		counter = 0;
	  }
	}
	else if (thread == 1) {
	  printf("%c\n", alphabet);
	  alphabet++;
	  if (alphabet == 123) {
		alphabet = 'a';
	  }
	}
	else {
	  printf("#\n");
	}

	for (int i = 0; i < 1000000; i++) {
	  sum = sum + i; 
	}
  }
}

int main(int argc, char **argv) {
  pthread_t threads[3];
  
  for (int i = 0; i < 3; i++) {
	pthread_create(&threads[i], NULL, char_print, (void *) i);
  }

  pthread_exit(NULL);
}


