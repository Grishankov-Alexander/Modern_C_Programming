/*
 * Program that calculates how many digits is in a number
*/


#include <stdio.h>


int main(void)
{
	int number, digits;

	printf("Enter a number: ");
	(void)scanf("%d", &number);

	if (number < 0) number = -number;
	if (number < 10)
		digits = 1;
	else if (number < 100)
		digits = 2;
	else if (number < 1000)
		digits = 3;
	else if (number < 10000)
		digits = 4;
	else {
		printf("Too much digits!\n");
		digits = 0;
	}

	printf("The number %d had %d digits.\n", number, digits);

	return 0;
}
