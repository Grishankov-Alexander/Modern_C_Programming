/*
 * Calculates greatest common divisor.
*/


#include <stdio.h>


int gcd(int m, int n)
{
	return n == 0 ? m : gcd(n, m % n);
}
		

int main(void)
{
    int m, n;

    printf("Enter two integers: ");
    (void)scanf("%d%d", &m, &n);

    printf("Greatest common divisor: %d\n", gcd(m, n));

    return 0;
}
