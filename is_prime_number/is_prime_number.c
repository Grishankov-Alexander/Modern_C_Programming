/*
 * Shows if number is a prime.
*/


#include <stdio.h>


int main(void)
{
	int n, d;

	printf("Enter a number: ");
	(void)scanf("%d", &n);

	for (d = 2; d * d <= n && n % d != 0; d++)
		;

	if (n % d == 0 && n != d)
		printf("%d is divisible by %d\n", n, d);
	else
		printf("%d is prime.\n", n);

	return 0;
}
