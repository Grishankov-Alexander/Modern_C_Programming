/*
 * Program that finds all even squares that are
 * less than the number entered.
*/


#include <stdio.h>


int main(void)
{
    int n, i, i_squared;

    printf("Enter a number: ");
    (void)scanf("%d", &n);

    for (i = 2; (i_squared = i * i) <= n; ++i)
        if (i_squared % 2 == 0)
            printf("%d\n", i_squared);

    return 0;
}
