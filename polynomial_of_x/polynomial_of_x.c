/*
 * Computes polynomial of specified x
*/

#include <stdio.h>

int main(void)
{
	float x, polynomial;

	printf("Enter X value: ");
	(void)scanf("%f", &x);

	polynomial = ((((3*x + 2)*x - 5)*x - 1)*x + 7)*x - 6;

	printf("Polynomial: %.2f\n", polynomial);

	return 0;
}

