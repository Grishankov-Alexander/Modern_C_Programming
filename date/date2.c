/*
 * You specify year and day of year (from 1 to 366).
 * Program then prints correct month and day numbers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


static int num_days_leap_february = 29;
static int num_days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};


static bool is_leap_year(int year)
{
	if (year % 400 == 0)		return true;
	else if (year % 100 == 0)	return false;
	else if (year % 4 == 0)		return true;
	else				return false;
}


static int num_days_in_year(int year)
{
	if (is_leap_year(year))	return 366;
	else			return 365;
}


static void split_date(int day_of_year, int year,
		int *month, int *day)
{
	int days_in_year, i;
	bool leap_year;

	leap_year = is_leap_year(year);
	days_in_year = num_days_in_year(year);

	// Exit if day_of_year is incorrect
	if (day_of_year <= 0 || day_of_year > days_in_year) {
		printf("Specified day should be between");
		printf(" 1 and %d for year %d\n", days_in_year, year);
		exit(EXIT_FAILURE);
	}

	for (i = 0; day_of_year > 0; i++)
		if (i == 1 && leap_year) {
			day_of_year -= num_days_leap_february;
			continue;
		} else
			day_of_year -= num_days_in_month[i];

	*month = i--;
	*day = i == 1 && leap_year
		? (29 + day_of_year)
		: (num_days_in_month[i] + day_of_year);
}


int main(void)
{
	int month, day;
	int day_of_year, year;

	printf("Enter year: ");
	scanf("%d", &year);
	printf("Enter day_of_year: (from 1 to 366) ");
	scanf("%d", &day_of_year);

	split_date(day_of_year, year, &month, &day);

	printf("Month: %d; Day: %d\n", month, day);

	return 0;
}
