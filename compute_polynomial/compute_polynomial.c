/*
 * Computes the value of equation
 * 3*x^5 + 2*x^4 - 5x^3 - x^2 + 7*x - 6
*/


#include <stdio.h>
int power(int n, int p);
int compute_poly(int x);


int main(void)
{
	int x;

	printf("Program computes the following equation:\n");
	printf("3 * x^5 + 2 * x^4 - 5 * x^3 - x^2 + 7 * x - 6\n");

	printf("Enter x: ");
	scanf("%d", &x);

	printf("Result: %d\n", compute_poly(x));

	return 0;
}


int power(int n, int p)
{
	if (p == 0)
		return 1;
	return n * power(n, p - 1);
}


int compute_poly(int x)
{
	return 3 * power(x, 5) + 2 * power(x, 4) - 5 * power(x, 3)
		- power(x, 2) + 7 * x - 6;
}
