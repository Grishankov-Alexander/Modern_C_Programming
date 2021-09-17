#include <stdio.h>
#include <ctype.h>

#include "readln.h"


int readln(char *s, int n)
{
	char *p = s;
	char c;

	// Skip whitespace
	while (isspace(c = getchar()))
		;
	while (c != EOF && c != '\n') {
		if (p >= s + n - 1) {
			ungetc(c, stdin);
			break;
		}
		*p++ = c;
		c = getchar();
	}

	*p = 0;

	return p - s;
}
