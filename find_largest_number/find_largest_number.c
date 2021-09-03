/*
 * Program that finds the largest number entered.
*/


#include <stdio.h>


int main(void)
{
	float n, largest;

	largest = 0.00f;
	printf("Enter a number: ");
	(void)scanf("%f", &n);

	while (n > 0.00f) {
		if (largest < n)
			largest = n;
		printf("Enter a number: ");
		(void)scanf("%f", &n);
	}

	if (largest > 0.00f)
		printf("Largest number was: %.2f\n", largest);

	return 0;
}
