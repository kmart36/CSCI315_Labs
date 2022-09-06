#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;

  Pipe(fd);
  pid = Fork();
  
  if (pid > 0) {
	// parent process
	close(fd[READ_END]);
	int i = -1;
	do {
	  i++;
	  Write(fd[WRITE_END], &write_msg[i], 1);
	} while (write_msg[i] != '\0');
 	close(fd[WRITE_END]);
  }
  else {
	// child process
	close(fd[WRITE_END]);
	int i = 0;
	int c;
	while (c != 0) {
	  c = Read(fd[READ_END], &read_msg[i], 1);
	  i++;
	} 
	printf("read %s\n", read_msg);
	close(fd[READ_END]);
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
