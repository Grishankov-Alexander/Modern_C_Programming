/*
 * Prints a table of squares using a for statement
*/


#include <stdio.h>


int main(void)
{
    long i, n;

    printf("Enter number of entries in table: ");
    // Skip trailing newline
    (void)scanf("%ld%*c", &n);

    printf("%ld ^ 2 = %ld\n", n, n * n);
    printf("Press Enter to print all squares between 1 and %ld: ", n);
    while (getchar() != (int) '\12')
        ;

    for (i = 1; i <= n; ++i) {
        printf("%ld\t%ld\n", i, i * i);
	if (i % 24 == 0) {
    	    printf("Press Enter to continue: ");
    	    while (getchar() != (int) '\12')
    	        ;
        }
    }

    return 0;
}
