/*
 * Program that reduces the fraction to its lowest terms.
*/


#include <stdio.h>


static int gcd(int m, int n);
static void reduce(
	int numer, int denom,
	int *reduced_numer, int *reduced_denom
);


int main(void)
{
    int n, d;

    printf("Enter a fraction: ");
    (void)scanf("%d /%d", &n, &d);


    reduce(n, d, &n, &d);

    printf("In lowest terms: %d/%d\n", n, d);

    return 0;
}


int gcd(int m, int n)
{
	return n == 0
		? m < 0 ? ~m + 1 : m
		: gcd(n, m % n);
}


void reduce(
	int numer, int denom,
	int *reduced_numer, int *reduced_denom
) {
	int g = gcd(numer, denom);
	*reduced_numer = numer / g;
	*reduced_denom = denom / g;
}
