/*
 * Sums a series of numbers.
*/


#include <stdio.h>


int main(void)
{
	long double n, sum = 0.0L;

	printf("This program sums series of doubles.\n");

	printf("Enter number (0 to exit): ");
	(void)scanf("%Lg", &n);
	while (n != 0.0L) {
		sum += n;
		printf("Enter number (0 to exit): ");
		(void)scanf("%Lg", &n);
	}

	printf("Sum: %Lg\n", sum);

	return 0;
}
