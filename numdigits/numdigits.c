/*
 * Prints number of digits in an integer.
*/


#include <stdio.h>


int main(void)
{
	int digits = 0, n;

	printf("Enter integer: ");
	(void)scanf("%d", &n);
	printf("The number %d has ", n);

	do {
		n /= 10;
		digits++;
	} while (n != 0);

	printf("%d digit(s).\n", digits);

	return 0;
}
