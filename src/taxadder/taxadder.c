/*
 * Adds tax to specified amount of money
*/

#include <stdio.h>

#define TAX 1.05f

int main(void)
{
	float dollars, total;

	printf("Enter the amount of money: ");
	(void)scanf("%f", &dollars);

	total = dollars * TAX;

	printf("Total amount with tax: %.2f\n", total);

	return 0;
}
