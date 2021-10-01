/*
 * Chapter 17 Exercises.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n==========\n")


/*
 * My wrapper around realloc.
 * If failure - free previously allocated memory and exit
 *
 * case 1: prevalloc 0, bytes 0 // dummy call - LET IT BE
 * case 2: prevalloc 1, bytes 0 // freeing - LET IT BE;
 * case 3: prevalloc 0, bytes 1 // malloc
 * case 4: prevalloc 1, bytes 1 // Shrink or grow
*/
void *mymalloc(void *prevalloc, size_t bytes)
{
	void *new;

	new = realloc(prevalloc, bytes);

	if (!new && bytes) {
		if (prevalloc)
			free(prevalloc);
		printf(	"\nAllocation failed. Exit status: FAILURE.\n"
			"\tmymalloc(%p, %zu)\n", prevalloc, bytes);
		exit(EXIT_FAILURE);
	}

	return new;
}


int main(void)
{
	// My malloc wrapper
	{
		PRINT_TOPIC(malloc wrapper);
		char *mystr;
		mystr = mymalloc(NULL, 0); // Allocates dummy memory. mystr != NULL
		mystr = mymalloc(mystr, 0); // Frees memory. mystr == NULL
		mystr = mymalloc(NULL, 1024); // Usual malloc
		mystr = mymalloc(mystr, 2048); // Reallocates
		printf("All OK\n");

		size_t sz = 1024UL;
		do {
			printf("mymalloc(%p, %zu)\n", (void *) mystr, sz);
			mystr = mymalloc(mystr, sz);
			memset(mystr, 0xff, sz);
			sz *= 16UL;
		} while (mystr);
	}


	return 0;
}
