/*
 * Encrypts the message
 * using XOR operation.
*/


#include <ctype.h>
#include <stdio.h>


#define KEY '&'


int main(void)
{
	char c, ec;

	while ((c = getchar()) != EOF) {
		ec = c ^ KEY;
		if (isprint(c) && isprint(ec))
			putchar(ec);
		else
			putchar(c);
	}

	return 0;
}
