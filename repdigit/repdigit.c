/*
 * Shows which digits were repeated in the number entered.
*/


#include <stdio.h>
#include <stdbool.h>


#define NUMBER_ELEMENTS(x) ((int) (sizeof(x) / sizeof(x[0])))

int main(void)
{
	long long n;
	unsigned num_occurs[10];
	int i;

	while (true) {
		printf("Enter a number (0 or less to terminate): ");
		(void)scanf("%lld", &n);
		if (n <= 0)
			break;

		for (i = 0; i < NUMBER_ELEMENTS(num_occurs); i++)
			num_occurs[i] = 0;

		while (n != 0) {
			++num_occurs[n % 10];
			n /= 10;
		}

		printf("%-15s", "Digit:");
		for (i = 0; i < NUMBER_ELEMENTS(num_occurs); i++)
			printf("%3d", i);
		printf("\n%-15s", "Occurences:");
		for (i = 0; i < NUMBER_ELEMENTS(num_occurs); i++)
			printf("%3d", num_occurs[i]);

		printf("\n");
	}

	return 0;
}
