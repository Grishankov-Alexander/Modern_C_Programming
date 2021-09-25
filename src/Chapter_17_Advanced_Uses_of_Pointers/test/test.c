/*
 * This file will outline chapter concepts
 *
 * Serves for educational and testing purposes.
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Prints topic name
#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n==========\n")


// Allocate memory for string argument
static char *alloc_string(const char *str);
// Concantenate s1 and s2 and allocate memory for them.
static char *concat(const char *s1, const char *s2);


int main(void)
{
	// String allocation
	{
		PRINT_TOPIC(String allocation);

		char *s1 = alloc_string("Hello world!");
		printf("s1: %s\n", s1);

		char *s2 = concat("Hello", " world!");
		printf("s2: %s\n", s2);

		free(s1);
		free(s2);
	}

	return 0;
}


static char *alloc_string(const char *str)
{
	char *p;

	p = malloc(strlen(str) + 1);
	if (!p)
		printf("Allocation failed\n");
	else
		strcpy(p, str);

	return p;
}


static char *concat(const char *s1, const char *s2)
{
	char *p;

	p = malloc(strlen(s1) + strlen(s2) + 1);
	if (!p)
		printf("Allocation failed!\n");
	else
		strcpy(p, s1), strcat(p, s2);
	
	return p;
}
