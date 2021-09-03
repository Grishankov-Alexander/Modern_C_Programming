/*
 * Raises x to power n
*/


#include <stdio.h>


long long power(int x, int n);


int main(void)
{
	int x, n;
	
	printf("Power: raises x to power n.\n");
	printf("Enter x and n: ");
	scanf("%d %d", &x, &n);

	printf("%d ^ %d = %lld\n", x, n, power(x, n));

	return 0;
}


long long power (int x, int n)
{
	long long res = 1;
	int i;

	for (i = 0; i < n; i++)
		res *= x;

	return res;
}
