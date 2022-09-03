#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char** argv) {
  int status;
  int pid;
  if (argc != 2) {
	printf("Wrong number of arguments.\n"); 
	return 0;
  }
  print_environment();
  if (pid = fork() == 0) {
	//child process
	execlp("/bin/cat", "/bin/cat", argv[1], (char*) NULL); 
  }
  else {
	//parent process
	wait(&status);
	if (WIFEXITED(status)) {
	  if (pid = fork() == 0) {
		//child process
		execlp("/usr/bin/wc", "/usr/bin/wc", argv[1], (char*) NULL);
	  }
	  else {
		//parent process
		wait(&status);
	  }
	}
  }
}

void print_environment(void) {
  int i = 0;
  while (environ[i]) {
	printf("%s\n", environ[i]);
	i++;
  }
}
