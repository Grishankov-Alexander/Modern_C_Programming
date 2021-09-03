/*
 * Program that converts phone number letters to digits.
*/


#include <stdio.h>
#include <ctype.h>


#define MAX_NUM 15
#define GET_CAPITAL (toupper(getchar()))


int main(void)
{
	int i;
	char c;
	char a[MAX_NUM];

	printf("Enter phone number: ");

	for (i = 0, c = GET_CAPITAL; c != '\n' && i < MAX_NUM; i++, c = GET_CAPITAL) {

		if (c < 'A' || 'Y' < c) {
			a[i] = c;
			continue;
		}

		switch (c) {
			case 'A': case 'B': case 'C':
				a[i] = '2';
				break;
			case 'D': case 'E': case 'F':
				a[i] = '3';
				break;
			case 'G': case 'H': case 'I':
				a[i] = '4';
				break;
			case 'J': case 'K': case 'L':
				a[i] = '5';
				break;
			case 'M': case 'N': case 'O':
				a[i] = '6';
				break;
			case 'P': case 'R': case 'S':
				a[i] = '7';
				break;
			case 'T': case 'U': case 'V':
				a[i] = '8';
				break;
			case 'W': case 'X': case 'Y':
				a[i] = '9';
				break;
			default:
				a[i] = c;
				break;
		}

	}

	printf("In numeric form: ");
	for (i = 0; i < MAX_NUM; i++)
		putchar(a[i]);

	printf("\n");

	return 0;
}
