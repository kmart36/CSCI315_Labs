#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc > 1) {
	char* s;
	for (int k = argc - 1; k > 0; k--) {
	  s = argv[k];
	  for (int i = strlen(s) - 1; i >= 0; i--) {
		printf("%c", s[i]);
	  }
	  printf(" ");
	}
	printf("\n");
  }
  else {
	printf("Incorrect number of arguments.\n");
  }
  return 0;
}
