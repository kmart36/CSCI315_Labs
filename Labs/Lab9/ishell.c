#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "wrapper.h"
#include "wrapper.c"

void execute(char **com) {  
  int status;
  int returnStat;
  int pid = Fork();
  
  if (pid == 0) {
	//child process
	returnStat = execvp(*com, com);
	if (returnStat < 0) {
	  printf("[ishell: program terminated abnormally][%d]\n", returnStat);
	  exit(1);
	}
  }
  else {
	//parent process
	while (wait(&status) != pid);
	if (status == 0) {
	  printf("[ishell: program terminated successfully]\n");
	}
  } 
}

void split(char **com, char *prompt) {
  char *token = NULL;
  int arg = 0;
  while (token = strtok_r(prompt, " ", &prompt)) {
	if (token[strlen(token) - 1] == ';') {
	  token[strlen(token) - 1] = 0;
	  com[arg] = token;
	  arg++;
	  execute(com);
	  arg = 0;
	}
	else {
	  com[arg] = token;
	  arg++;
	}
  }
  com[arg] = NULL;
}

int main(int argc, char *argv[]) {
  char *com[256];
  
  while (1) {
	char *prompt = readline("ishell> ");

	split(com, prompt);

	execute(com);
  }
}
