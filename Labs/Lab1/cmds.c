#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc == 5) {
	char c = argv[1][0];
	int i = atoi(argv[2]);
	float f = atof(argv[3]);
	char* s = argv[4];
	printf("%c %d %f %s\n", c, i, f, s);
  }
  else {
	printf("Incorrect number of arguments.\n");
  }
  return 0;
}
