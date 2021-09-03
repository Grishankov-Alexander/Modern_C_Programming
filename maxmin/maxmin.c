/*
 * Finds the largest and smallest elements in an array
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 10


void max_min(int a[], int n, int *max, int *min);


int main(void)
{
	int a[N], *p, max, min;

	srand((unsigned) time(NULL));

	for (p = a; p < a + N; p++)
		*p = rand() % 100;

	max_min(a, N, &max, &min);

	printf("Generated array:");
	for (p = a; p < a + N; p++)
		printf(" %d", *p);

	printf("\nMax = %d\nMin = %d\n", max, min);

	return 0;
}


void max_min(int a[], int n, int *max, int *min)
{
	*max = *min = *a++;
	for ( ; n > 1; n--, a++)
		*a > *max ? *max = *a : (*a < *min ? *min = *a : 0);
}
