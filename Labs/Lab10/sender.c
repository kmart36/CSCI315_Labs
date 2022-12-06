#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  sem_t *rec, *send;

  char message[300];
  FILE *fd;
  if (argc != 2) {
	printf(" usage: ./sender [message]\n");
	exit(-1);
  }

  fd = fopen("channel.txt", "a");
  strcpy(message, argv[1]);

  rec = sem_open("rec", O_CREAT, 0777, 1);
  send = sem_open("send", O_CREAT, 0777, 0);

  sem_wait(rec);

  fprintf(fd, "%s\n", message);

  sem_post(send);
  sem_post(rec);

  fclose(fd);
}
