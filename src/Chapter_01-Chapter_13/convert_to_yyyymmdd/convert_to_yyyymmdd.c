/*
 * Program that accepts date in the form mm/dd/yyyy
 * and converts the output to yyyymmdd
*/

#include <stdio.h>

int main(void)
{
	int m, d, y;

	printf("Enter a date (mm/dd/yyyy): ");
	(void)scanf("%d/%d/%d", &m, &d, &y);

	printf("You entered the date: %.4d%.2d%.2d\n", y, m, d);

	return 0;
}

