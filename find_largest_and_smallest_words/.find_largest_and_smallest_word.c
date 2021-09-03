/*
 * Interactive program
 * Reads words from program parameters.
 * Prints which word comes first and which last (in dictionary order).
*/


#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
	char **p;
	char *smallest, *largest;

	if (argc > 1)
		smallest = largest = *(p = argv + 1);
	else
		smallest = largest = "";

	for (p = argv + 2; p < argv + argc; p++) {
		if (strcmp(*p, largest) > 0)
			largest = *p;
		else if (strcmp(*p, smallest) < 0)
			smallest = *p;

	}

	printf("Smallest word: %s\n", smallest);
	printf("Largest word: %s\n", largest);
}
