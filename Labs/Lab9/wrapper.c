#include "wrapper.h"
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h>
#include <pthread.h>

int Pipe(int pipefd[2]) {
  int pid = pipe(pipefd);
  if (pid == -1) {
    perror("Pipe Error: ");
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
    perror("Fork Error: ");
    exit(-1);
  }
  return pid;
}

pid_t Wait(int *wstatus) {
  pid_t pid = wait(wstatus);
  if (pid == -1) {
	perror("Wait Error: ");
	exit(-1);
  }
  return pid;
}

pid_t Waitpid(pid_t pid, int *wstatus, int options) {
  pid_t id = waitpid(pid, wstatus, options);
  if (id == -1) {
    perror("Waitpid Error: ");
    exit(-1);
  }
  return id;
}

int Open(const char *pathname, int flags) {
  int pid = open(pathname, flags);
  if (pid == -1) {
    perror("Open Error: ");
    exit(-1);
  }
  return pid;
}

int Close(int fd) {
  int pid = close(fd);
  if (pid == -1) {
    perror("Close Error: ");
    exit(-1);
  }
  return pid;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int pid = connect(sockfd, addr, addrlen);
  if (pid == -1) {
    perror("Connect Error: ");
    exit(-1);
  }
  return pid;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int pid = bind(sockfd, addr, addrlen);
  if (pid == -1) {
    perror("Bind Error: ");
    exit(-1);
  }
  return pid;
}

int Listen(int sockfd, int backlog) {
  int pid = listen(sockfd, backlog);
  if (pid == -1) {
    perror("Listen Error: ");
    exit(-1);
  }
  return pid;
}

int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen) {
  int pid = accept(sockfd, addr, addrlen);
  if (pid == -1) {
    perror("Accept Error: ");
    exit(-1);
  }
  return pid;
}
