/*
 * Finds factorial of a positive integer.
*/


#include <stdio.h>


long double fact(int x)
{
	long double f = 1.0L;

	while (x > 1.0L)
		f *= x--;

	return f;
}


int main(void)
{
	int x;

	printf("Enter a number: ");
	scanf("%d", &x);

	printf("%d! = %.3Lg\n", x, fact(x));

	return 0;
}
