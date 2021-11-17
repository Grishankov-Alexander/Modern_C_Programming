/*
 * fcopy - Copy a file.
 *
 * Usage: fcopy source dest
*/


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int c;
	FILE *src, *dst;

	if (argc != 3) {
		fprintf(stderr, "Usage: fcopy <source> <destination>\n");
		exit(EXIT_FAILURE);
	}
	if ((src = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Can't open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if ((dst = fopen(argv[2], "wb")) == NULL) {
		fclose(src);
		fprintf(stderr, "Can't open %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	while ((c = getc(src)) != EOF)
		putc(c, dst);

	fclose(src);
	fclose(dst);

	return 0;
}
