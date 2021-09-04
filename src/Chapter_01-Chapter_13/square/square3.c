/*
 * Prints a table of squares using an odd method
*/


#include <stdio.h>


int main(void)
{
    int i, n, square, odd;

    printf("Enter number of entries in the table: ");
    (void)scanf("%d", &n);

    for (i = square = 1, odd = 3; i <= n; i++, square += odd, odd += 2)
	    printf("%10d%10d\n", i, square);

    return 0;
}
