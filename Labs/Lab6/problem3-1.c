#include <stdio.h>
#include <pthread.h>
#include <features.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


void *Philosopher(void *id);
void napping(int t);
pthread_mutex_t chopsticks[5];


int main() {
  pthread_t threads[5];
  for (int i = 0; i < 5; i++) {
	pthread_mutex_init(&chopsticks[i], NULL);
  }
  for (int i = 0; i < 5; i++) {
	pthread_create(&threads[i], NULL, Philosopher, (void *) i);
  }
  pthread_exit(NULL);
}

void *Philosopher(void *id) {
  long long n_id = (long long) id;
  while (1) {
	printf("Philosopher %lld is thinking.\n", n_id);
	napping(1); 
	printf("Philosopher %lld is hungry.\n", n_id);
	if (n_id % 2 == 1) {
	  pthread_mutex_lock(&chopsticks[n_id]);
	  printf("Philosopher %lld is picking up chopstick %lld\n", n_id, n_id);
	  // The philosophers will wait a long time before picking up another chopstick. This makes it so all of the left chopsticks are picked up before any right ones, creating a deadlock. 
	  napping(10);
	  pthread_mutex_lock(&chopsticks[(n_id + 1) % 5]);
	  printf("Philosopher %lld is picking up chopstick %lld\n", n_id, (n_id + 1) % 5);
	}
	else {
	  pthread_mutex_lock(&chopsticks[(n_id + 1) % 5]);
	  printf("Philosopher %lld is picking up chopstick %lld\n", n_id, (n_id + 1) % 5);
	  // The philosophers will wait a long time before picking up another chopstick. This makes it so all of the left chopsticks are picked up before any right ones, creating a deadlock. 
	  napping(10);
	  pthread_mutex_lock(&chopsticks[n_id]);
	  printf("Philosopher %lld is picking up chopstick %lld\n", n_id, n_id);

	}
	printf("Philosopher %lld is starting to eat.\n", n_id);
	napping(1);
	printf("Philosopher %lld is done eating.\n", n_id);
	pthread_mutex_unlock(&chopsticks[(n_id + 1) % 5]);
	printf("Philosopher %lld is putting down chopstick %lld\n", n_id, (n_id + 1) % 5);
	pthread_mutex_unlock(&chopsticks[n_id]);
	printf("Philosopher %lld is putting down chopstick %lld\n", n_id, n_id);
	fflush(stdout);
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

