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


	// Restricted Pointers
	// I don't understand - no warnings for code below.
	{
		PRINT_TOPIC(Restricted Pointers);

		int a = 5;
		int * restrict p;
		int * restrict q;

		p = &a;
		*p = 6;

		q = p;
		printf("*q = %d\n", *q);

		*q = 7;
	}


	// Flexible array members
	{
		PRINT_TOPIC(Flexible array Members C99);

		// Struct hack - before C99
		struct vstring {
			int n;
			char str[4];
		};

		int strsize = 5;
		const char *mystr = "abcd";

		// Should allocate 9 bytes
		struct vstring *vstr = malloc(sizeof *vstr - sizeof vstr->str + strsize);
		printf("sizeof *vstr = %zu\n", sizeof *vstr - sizeof vstr->str + strsize);

		vstr->n = strlen(mystr) + 1;
		strcpy(vstr->str, mystr);
		printf("vstr->str = %s\n", vstr->str);

		free(vstr);


		// C99 Flexible array members
		// P.S. struct flexvstr - incomplete type
		struct flexvstr {
			int size;
			char str[];
		};

		printf("\nsizeof (flexvstr) = %zu\n", sizeof (struct flexvstr));

		struct flexvstr *fvstr = malloc(sizeof *vstr + strsize);
		fvstr->size = strsize;
		strcpy(fvstr->str, mystr);
		free(fvstr);

		// Only array of pointers is possible
		struct flexvstr *fvstrarr[2] = {
			malloc(sizeof **fvstrarr + sizeof "abcde"),
			malloc(sizeof **fvstrarr + sizeof "fghij"),
		};
		free(fvstrarr[0]);
		free(fvstrarr[1]);
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
