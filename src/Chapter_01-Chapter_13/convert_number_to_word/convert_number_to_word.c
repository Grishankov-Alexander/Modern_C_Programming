/*
 * Program that asks for a 2-digit number
 * and converts it to word
*/


#include <stdio.h>
#include <string.h>


// Array that represents words for tenths
static const char *tenths[] = {
	"ten", "twenty", "thirty", "fourty",
	"fifty", "sixty", "seventy", "eighty",
	"ninety"
};
// Array that represents words for ones
static const char *ones[] = {
	"one", "two", "three", "four",
	"five", "six", "seven", "eight",
	"nine"
};
// Array that represents digits from 11 to 19
static const char *spec_numbers[] = {
	"eleven", "twelve", "thirteen", "fourteen",
	"fifteen", "sixteen", "seventeen", "eighteen",
	"nineteen"
};


int main(void)
{
	int fd, sd;

	printf("Enter 2-digit number: ");
	if (scanf("%1d%1d", &fd, &sd) != 2)
		return 1;

	if (fd == 0 && sd == 0)	printf("zero");
	else if (fd == 0)	printf("%s", ones[sd - 1]);
	else if (sd == 0)	printf("%s", tenths[fd - 1]);
	else if (fd == 1)	printf("%s", spec_numbers[sd - 1]);
	else			printf("%s-%s", tenths[fd - 1], ones[sd - 1]);

	printf("\n");

	return 0;
}
