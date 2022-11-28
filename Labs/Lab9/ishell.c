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
  int returnStat;
  int status;
  
  while (1) {
	char *prompt = readline("ishell> ");
	
	
	split(com, prompt);
	
	int pid = Fork();
	
	if (pid > 0) {
	  //parent process
	  wait(&status);
	  if (status == 0) {
		printf("[ishell: program terminated successfully]\n");
	  }
	}
	else {
	  //child process
 	  returnStat = execvp(*com, com);
	  if (returnStat < 0) {
		printf("[ishell: program terminated abnormally][%d]\n", returnStat);
		exit(1);
	  }
	}
  }
}
