/*
 * Sums a series of numbers
*/


#include <stdio.h>


int main(void)
{
    int n, sum = 0;

    printf("This program sums a series of integers.\n");
    printf("Enter integers (0 to terminate): ");
    
    (void)scanf("%d", &n);
    while (n != 0) {
        sum += n;
        (void)scanf("%d", &n);
    }

    printf("Sum: %d\n", sum);

    return 0;
}
