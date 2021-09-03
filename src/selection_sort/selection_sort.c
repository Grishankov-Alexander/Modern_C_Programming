/*
 * Recursive selection sort.
*/


#include <stdio.h>


#define SIZE 10


static void ssort(int a[], int n);


void ssort(int a[], int n)
{
	int i, temp;
	int il = 0;

	if (n == 1)
		return;

	for (i = 0; i < n; i++)
		if (a[i] > a[il])
			il = i;

	temp = a[--i];
	a[i] = a[il];
	a[il] = temp;

	ssort(a, i);
}


int main(void)
{
	int a[SIZE];
	int i;

	printf("Enter %d integers: ", SIZE);
	for (i = 0; i < SIZE; i++)
		scanf("%d", &a[i]);

	ssort(a, SIZE);

	printf("Sorted array:");
	for (i = 0; i < SIZE; i++)
		printf(" %d", a[i]);

	printf("\n");

	return 0;
}
