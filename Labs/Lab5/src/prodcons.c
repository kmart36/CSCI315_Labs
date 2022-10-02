/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include <pthread.h>

#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX)
 *
 *  where RAND_MAX is the largest random number returned
 *  by rand_r. There are potential problems here in this computation,
 *  for example, it is possible that the value computed will be out 
 *  of range or will become zero.
 *
 *  Please make sure you think through this issue and revise
 *  the code so that a correct and meaningful value can be
 *  generated for the desired effect.
 *  
 *  You are responsible to come up with a correct solution.
 */
#define SCALE_FACTOR 1000

// global variables -----------------------

struct circular_list mylist;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = 1234;
  int r;
  //  int n = 0;
  while (1) {
	//n++;
	/* The following solution to compute the amount of time to sleep
	 * is incorrect. You MUST fix it. See the "SCALE_FACTOR ..." comment
	 * section above.
	 */ 
    // sleep for random period of time
	r = rand_r(&seed);
	//printf("Random Amount of Sleep (producer): %d\n", r);
    usleep(SCALE_FACTOR * seed / r); 
    
    // generate a random number
	r = rand_r(&seed);
	//printf("Random Item: %d\n", r);
    i = (item) (((double) r) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
  }
}

void *consumer (void *param) {
  item i;
  unsigned int seed = 999;
  int r;
  //  int n = 0;
  while (1) {
	//n++;
    // sleep for random period of time
	r = rand_r(&seed);
	//printf("Random Amount of Sleep (consumer): %d\n", r);
    usleep(SCALE_FACTOR * seed / r);

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
  }
}

int main (int argc, char *argv[]) {

  // get command line arguments
  if (argc < 4) {
	printf("Usage: ./prodcons [num_prod] [num_cons] [sleep time]\n");
	exit(-1);
  }
  // if error in command line argument usage, terminate with helpful
  // message

  int prods = atoi(argv[1]);
  int cons = atoi(argv[2]);
  int sleep_time = atoi(argv[3]);
  
  // initialize buffer
  circular_list_create(&mylist, 20);
  
  // create producer thread(s)

  pthread_t prod_threads[prods];
  int perr;
  for (int i = 0; i < prods; i++) {
	perr = pthread_create(&prod_threads[i], NULL, producer, (void*)&i);
	if (perr == -1) {
	  perror("Error: producer thread\n");
	  exit(-1);
	}
  }
  // create consumer thread(s)

  pthread_t con_threads[cons];
  int cerr;
  for (int i = 0; i < cons; i++) {
	cerr = pthread_create(&con_threads[i], NULL, consumer, (void*)&i);
	if (cerr == -1) {
	  perror("Error: consumer thread\n");
	  exit(-1);
	}
  }
  // sleep to give time for threads to run

  sleep(sleep_time);
  // exit
  return (0);
}
