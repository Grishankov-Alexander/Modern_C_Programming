/*
 * Sorts an array of integers using Quicksort algorithm.
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define N 10


static void quicksort(int *low, int *high);
static int *split(int *low, int *high);


int main(void)
{
	int a[N], *p = a;

	srand((unsigned) time(NULL));

	for ( ; p < a + N; p++)
		*p = rand() % 100;

	printf("Unsorted array:");
	for (p = a; p < a + N; p++)
		printf(" %d", *p);

	quicksort(a, p - 1);

	printf("\nSorted array:");
	for (p = a; p < a + N; p++)
		printf(" %d", *p);

	printf("\n");

	return 0;
}


static void quicksort(int *low, int *high)
{
	int *middle;

	if (low >= high)
		return;
	middle = split(low, high);
	quicksort(low, middle - 1);
	quicksort(middle + 1, high);
}

static int *split(int *low, int *high)
{
	int part_el = *low;

	for ( ; ; ) {
		while (low < high && part_el <= *high)
			high--;
		if (low >= high)
			break;
		*low++ = *high;

		while (low < high && *low <= part_el)
			low++;
		if (low >= high)
			break;
		*high-- = *low;
	}
	*high = part_el;

	return high;
}
