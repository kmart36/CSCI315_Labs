#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int Read(int fd, void *buf, size_t count);
int Write(int fd, const void *buf, size_t count);
int Pipe(int pipefd[2]);
int Fork(void);

int main(void) {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];  
  int p2c[2];
  int c2p[2];
  pid_t pid;

  Pipe(p2c);
  Pipe(c2p);
  pid = Fork();
  
  if (pid > 0) {
	// parent process

	// writing to parent-to-child pipe
	close(p2c[READ_END]);
	int i = -1;
	do {
	  i++;
	  Write(p2c[WRITE_END], &write_msg[i], 1);
	} while (write_msg[i] != '\0');
 	close(p2c[WRITE_END]);

	// reading from child-to-parent pipe
	close(c2p[WRITE_END]);
	int j = 0;
	int c = 1;
	while (c != 0) {
	  c = Read(c2p[READ_END], &read_msg[j], 1);
	  if (c != 0) {
		printf("%c", read_msg[j]);
	  }
	  j++;
	}
	printf("\n");
	close(c2p[READ_END]);
  }
  else {
	// child process

	// reading from parent-to-child pipe
	close(p2c[WRITE_END]);
	int i = 0;
	int c;
	do {
	  c = Read(p2c[READ_END], &read_msg[i], 1);
	  if (c != 0) {
		printf("%c", read_msg[i]);
	  }
	  i++;
	} while (c != 0);
	printf("\n");
	close(p2c[READ_END]);

	// writing to child-to-parent pipe
	close(c2p[READ_END]);
	int j = -1;
	do {
	  j++;
	  write_msg[j] = toupper(read_msg[j]);
	  Write(c2p[WRITE_END], &write_msg[j], 1);
	} while (write_msg[j] != '\0');
	close(c2p[WRITE_END]);
  }

  return 0;
}

int Pipe(int pipefd[2]) {
  int pid = pipe(pipefd);
  if (pid == -1) {
	perror("Error: ");
	exit(-1);
  }
  return pid;
}

int Read(int fd, void *buf, size_t count) {
  int pid = read(fd, buf, count);
  if (pid == -1) {
	perror("Error: ");
	exit(-1);
  }
  return pid;
}

int Write(int fd, const void *buf, size_t count) {
  int pid = write(fd, buf, count);
  if (pid == -1) {
	perror("Error: ");
	exit(-1);
  }
  return pid;
}

pid_t Fork(void) {
  int pid = fork();
  if (pid == -1) {
	perror("Error: ");
	exit(-1);
  }
  return pid;
}
