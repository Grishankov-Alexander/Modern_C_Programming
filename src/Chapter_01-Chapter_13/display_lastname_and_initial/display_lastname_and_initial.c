/*
 * Program that takes First name and Last name
 * and displays lastname followed by initial.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


//#define LAST_NAME_SZ 20
#define MAX_NAME_SIZE 40


static char *reverse_name(char *name);


int main(void)
{
	char name[MAX_NAME_SIZE];

	printf("Enter <FirstName LastName>: ");
	fgets(name, sizeof name, stdin);
	*(name + strlen(name) - 1) = 0;

	printf("Result: %s\n", reverse_name(name));

	return 0;
}


static char *reverse_name(char *name)
{
	char fni, *pln, *pn = name;

	// Find first name initial
	for (pln = name; *pln && !isalpha(*pln); pln++)
		;
	fni = *pln;

	// Skip first name (until space)
	for ( ; *pln && isalpha(*pln); pln++)
		;
	// Find last name beginning (skip space)
	for ( ; *pln && !isalpha(*pln); pln++)
		;

	// write last name
	while (*pln && isalpha(*pln))
		*pn++ = *pln++;
	// write comma
	if (*pn)
		*pn++ = ',';
	// write space
	if (*pn)
		*pn++ = ' ';
	// write first name initial
	if (*pn && fni)
		*pn++ = toupper(fni);
	// write period
	if (*pn)
		*pn++ = '.';

	// write terminating null
	*pn = 0;

	return name;
}
