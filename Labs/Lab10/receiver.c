#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  sem_t *rec, *send;

  char message[300];
  FILE *fd;

  fd = fopen("channel.txt", "rb");

  sem_unlink("rec");
  sem_unlink("send");

  rec = sem_open("rec", O_CREAT, 0777, 1);
  send = sem_open("send", O_CREAT, 0777, 0);

  while (1) {
	sem_wait(send);
	sem_wait(rec);

	if (fgets(message, sizeof(message), fd) != NULL) {
	  printf("receiver [msg arrival]: %s\n", message);
	}
	sem_post(rec);	
  }
}
