/*
 * Program that takes First name and Last name
 * and displays lastname followed by initial.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define LAST_NAME_SZ 20


int main(void)
{
	char last_name[LAST_NAME_SZ] = {0};
	char fni, ch;
	int i = 0, j = 0;
	fni = ch = (char)0;
	bool skip_fn = false;

	printf("Enter a first and last name: ");

	while ((ch = getchar()) != '\n' && i < LAST_NAME_SZ) {
		if (ch == ' ') {
			if (skip_fn)
				skip_fn = false;
			continue;
		}
		else if (!fni) {
			fni = ch;
			skip_fn = true;
			continue;
		}
		else if (!skip_fn)
			last_name[i++] = ch;
	}

	for (j = 0; j < i; ++j)
	       putchar(last_name[j]);	
	printf(", %c.\n", fni);

	return 0;
}
