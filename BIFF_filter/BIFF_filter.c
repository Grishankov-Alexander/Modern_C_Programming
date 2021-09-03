/*
 * Program that rewrites your message
 * in cool and unique way.
*/


#include <stdio.h>
#include <ctype.h>


int main(void)
{
	char c;

	printf("Enter message: ");

	while ((c = getchar()) != '\n') {
		c = toupper(c);
		switch (c) {
			case 'A':
				c = '4';
				break;
			case 'B':
				c = '8';
				break;
			case 'E':
				c = '3';
				break;
			case 'I':
				c = '1';
				break;
			case 'O':
				c = '0';
				break;
			case 'S':
				c = '5';
				break;
		}
		putchar(c);
	}
	printf("!!!!!!!!!!!\n");

	return 0;
}
