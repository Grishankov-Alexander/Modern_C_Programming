/*
 * Program that prints a calendar for one month.
*/


#include <stdio.h>


int main(void)
{
    int n, d, i;

    printf("Enter number of days in month: ");
    (void)scanf("%2d", &n);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    (void)scanf("%1d", &d);

    printf(" Su Mo Tu We Th Fr Sa\n");
    for (int j = 1; j < d; ++j)
        printf("   ");
    for (i = 1; i <= n; ++i, ++d) {
        printf("%3d", i);
        if (d == 7)
            printf("\n"), d = 0;
    }
    printf("\n");

    return 0;
}
