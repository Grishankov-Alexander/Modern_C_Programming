/*
 * Program that estimates wind force
*/


#include <stdio.h>


int main(void)
{
	int knots;

	printf("Enter wind speed (knots): ");
	(void)scanf("%d", &knots);

	if (knots < 1)
		printf("Calm");
	else if (knots < 4)
		printf("Light Air");
	else if (knots < 28)
		printf("Breeze");
	else if (knots < 48)
		printf("Gale");
	else if (knots < 64)
		printf("Storm");
	else
		printf("Hurricane");
	printf("\n");

	return 0;
}
