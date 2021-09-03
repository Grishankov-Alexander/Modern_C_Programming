/*
 * Reverses a series of numbers using a variable-length
 * array - C99 Only
*/


#include <stdio.h>


#define NUM_ELEMENTS(x) ((int) (sizeof(x) / sizeof(x[0])))


int main(void)
{
	int n, i;

	printf("How many numbers to you want to reverse ? ");
	(void)scanf("%d", &n);

	int a[n];

	printf("Enter %d numbers: ", n);
	for (i = 0; i < NUM_ELEMENTS(a); i++)
		(void)scanf("%d", &a[i]);

	printf("In reverse order:");
	for (i = NUM_ELEMENTS(a) - 1; i >= 0; i--)
		printf(" %d", a[i]);
	printf("\n");

	return 0;
}
