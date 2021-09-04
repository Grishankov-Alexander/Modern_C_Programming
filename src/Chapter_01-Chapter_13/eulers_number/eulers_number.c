/*
 * Program that computes approximate Eulers number
*/


#include <stdio.h>


int main(void)
{
	float eulers = 1.00f, fac, lowest_term;
	int i, j; 

	printf("Enter lowest term (0.25): ");
	(void)scanf("%f", &lowest_term);

	for (i = fac = 1; ; i += fac = 1) {
		for (j = 2; j <= i; j++)
			fac *= j;
		if (1 / fac < lowest_term)
			break;
		else
			eulers += 1 / fac;
	}

	printf("The resulting Eulers number is: %.10f\n", eulers);

	return 0;
}
