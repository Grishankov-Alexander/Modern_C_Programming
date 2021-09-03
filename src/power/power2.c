/*
 * Raises x to the power n.
*/


#include <stdio.h>


long long power(long long x, long long n)
{
	if (n == 0)
		return 1;

	// x^4 == (x^2)^2
	if (n % 2 == 0) {
		x = power(x, n / 2);
		return x * x;
	}
	
	return x * power(x, n - 1);
}


int main(void)
{
	long long x, n;

	printf("Raises x to the power of n.\n");
	printf("Enter x and n: ");
	scanf("%lld %lld", &x, &n);

	printf("%lld ^ %lld = %lld\n", x, n, power(x, n));

	return 0;
}
