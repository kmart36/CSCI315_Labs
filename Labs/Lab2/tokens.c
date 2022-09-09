#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define READ_END 0
#define WRITE_END 1

int Read(int fd, void *buf, size_t count);
int Write(int fd, const void *buf, size_t count);
int Pipe(int pipefd[2]);
int Fork(void);

int main(void) {
  char *write_msg;
  char *read_msg;  
  int p2c[2];
  int c2p[2];
  pid_t pid;

  Pipe(p2c);
  Pipe(c2p);

  pid= Fork();

  
  if (pid != 0) {
	close(p2c[READ_END]);
	close(c2p[WRITE_END]);
	while (1) {
	  // parent process
	  write_msg = readline("");
	  // writing to parent-to-child pipe
	  int leng1 = strlen(write_msg) + 1;
	  Write(p2c[WRITE_END], (void *) &leng1, sizeof(int));
	  Write(p2c[WRITE_END], write_msg, leng1);
	  
	  // reading from child-to-parent pipe
	  int leng2 = 0;
	  Read(c2p[READ_END], (void *) &leng2, sizeof(int));
	  read_msg  = malloc(leng2 * sizeof(char));
	  Read(c2p[READ_END], read_msg, leng2);
	  printf("new message: %s\n", read_msg);
	}
  }
  else {
	close(p2c[WRITE_END]);
	close(c2p[READ_END]);
	while (1) {
	  // child process
	  // reading from parent-to-child pipe
	  int leng1 = 0;
	  Read(p2c[READ_END], (void *) &leng1, sizeof(int));
	  read_msg = malloc(leng1 * sizeof(char));
	  Read(p2c[READ_END], read_msg, leng1);
	  
	  char* token = strtok(read_msg," ");
	  char* new_msg = malloc(leng1 * sizeof(char));
	  new_msg[0] = '\0';
	  
	  while (token != NULL) {
		strcat(new_msg, token);
		strcat(new_msg, " ");
		token = strtok(NULL, " ");
	  }
	  
	  // writing to child-to-parent pipe
	  int leng2 = strlen(new_msg) + 1;
	  Write(c2p[WRITE_END], (void *) &leng2, sizeof(int)); 
	  Write(c2p[WRITE_END], new_msg, leng2);
	}
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
	perror("Read Error: ");
	exit(-1);
  }
  return pid;
}

int Write(int fd, const void *buf, size_t count) {
  int pid = write(fd, buf, count);
  if (pid == -1) {
	perror("Write Error: ");
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
