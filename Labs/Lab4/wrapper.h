#ifndef WRAPPER_H
#define WRAPPER_H
#include <stddef.h>
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

pid_t Fork(void);

int Pipe(int pipefd[2]);

int Read(int fd, void *buf, size_t count);

int Write(int fd, const void *buf, size_t count);

pid_t Wait(int *wstatus);

pid_t Waitpid(pid_t pid, int *wstatus, int options);

int Open(const char *pathname, int flags);

int Close(int fd);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);

#endif 
