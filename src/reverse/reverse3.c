/*
 * Prints numbers in array from last to first using pointers technique
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10


int main(void)
{
	int a[N], *p;

	srand((unsigned) time(NULL));

	printf("Generated array:");
	for (p = a; p < a + N; p++)
		printf(" %d", *p = rand() % 100);

	printf("\nReverse order:");
	for (p = a + N - 1; p >= a; p--)
		printf(" %d", *p);

	printf("\n");

	return 0;
}
