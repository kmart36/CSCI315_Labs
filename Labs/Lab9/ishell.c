#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "wrapper.h"
#include "wrapper.c"

void split(char **com, char *prompt) {
  char *token = NULL;
  int arg = 0;
  while (token = strtok_r(prompt, " ", &prompt)) {
	com[arg] = token;
	arg += 1;
  }
}

int main(int argc, char *argv[]) {
  char *com[256];
  
  while (1) {
	char *prompt = readline("ishell> ");

	split(com, prompt);
	
	int pid = Fork();
	
	if (pid > 0) {
	  //parent process
	  wait(NULL);
	}
	else {
	  //child process
	  execvp(*com, com);
	}
  }
}
