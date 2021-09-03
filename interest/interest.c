/*
 * Program that computer interest rate over
 * specified number of years.
*/


#include <stdio.h>


#define NUM_ELEMENTS(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define INIT_BALANCE 50000.00


int main(void)
{
	double value[5];
	int low_rate, num_years, year, month, i;

	printf("Enter interest rate: %%");
	(void)scanf("%d", &low_rate);
	printf("Enter number of years: ");
	(void)scanf("%d", &num_years);

	printf("\nYears");
	for (i = 0; i < NUM_ELEMENTS(value); i++) {
		value[i] = INIT_BALANCE;
		printf("%10d%%", low_rate + i);
	}

	for (year = 1; year <= num_years; year++) {
		printf("\n%3d%4s", year, "");
		for (i = 0; i < NUM_ELEMENTS(value); i++) {
			for (month = 1; month <= 12; ++month)
				value[i] += (low_rate + i) / 1200.00 * value[i];
			printf("%11.2lf", value[i]);
		}
	}
	printf("\n");

	return 0;
}
