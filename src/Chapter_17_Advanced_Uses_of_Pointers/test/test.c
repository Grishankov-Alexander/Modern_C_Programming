/*
 * This file will outline chapter concepts
 *
 * Serves for educational and testing purposes.
*/


#include <stdlib.h>
#include <stdio.h>


// Prints topic name
#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n==========\n")


// Allocate memory for string argument
static char *store_string(const char *str);
// Concantenate s1 and s2 and allocate memory for them.
static char *concat(const char *s1, const char *s2);


int main(void)
{
	// Topic 1
	{
		PRINT_TOPIC(Topic, 1);
	}

	return 0;
}
