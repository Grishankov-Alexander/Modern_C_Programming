/*
 * Definitions for working with input words
*/


#include <stdio.h>
#include <ctype.h>
#include "word.h"


/* Reads at most n - 1 characters into word */
char *read_word(char *word, int n)
{
	char c, *p = word;

	// Skip spaces
	while (isspace(c = getchar()))
		;
	// Read until space or EOF
	while (c != EOF) {
		if (isspace(c) || p >= word + n - 1) {
			ungetc(c, stdin);
			break;
		}
		*p++ = c;
		c = getchar();
	}

	*p = 0;

	return word;
}
