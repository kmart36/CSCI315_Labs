#include <stdio.h>
#include <stdlib.h>

#include "hexdump.c"


int main(int argc, char *argv[]) {
  if (argc < 4) {
	printf("Usage: ./fdump [char *filename] [unsigned int offset] [unsigned int size]\n");
	exit(1);
  }
  char buf[256];
  char *filename = argv[1];
  unsigned int offset = atoi(argv[2]);
  unsigned int size = atoi(argv[3]);

  FILE *fp = fopen(filename, "r");

  fseek(fp, offset, SEEK_SET);

  fgets(buf, size, fp);

  hexdump(buf, size);

  printf("\n");
}
