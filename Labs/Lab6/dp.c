#include <stdio.h>
#include <pthread.h>
#include <features.h>
#include <stdlib.h>
#include <unistd.h>

void *Philosopher(void *id);
void napping(int t);

int main() {
  pthread_t threads[5];
  for (int i = 0; i < 5; i++) {
	pthread_create(&threads[i], NULL, Philosopher, (void *) i);
  }

  pthread_exit(NULL);
}

void *Philosopher(void *id) {
  while (1) {
	printf("Philosopher %lld is thinking.\n", (long long) id);
	napping(2); 
	printf("Philosopher %lld is hungry.\n", (long long) id);
	printf("Philosopher %lld is starting to eat.\n", (long long) id);
	napping(1);
	printf("Philosopher %lld is done eating.\n", (long long) id);
  }
}

void napping(int t) {
  unsigned int seed = rand();
  int r = rand_r(&seed) % (t * 1000);
  int seconds = r / 1000;
  int milliseconds = r % 1000;
  sleep(seconds);
  usleep(milliseconds * 1000);
}

