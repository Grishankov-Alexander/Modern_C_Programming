/*
 * Prints a date in legal form
*/


#include <stdio.h>


static char *months[] = {
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December"
};


int main(void)
{
	int day, month, year;

	printf("Enter date (mm/dd/yy): ");
	scanf("%d /%d /%d", &month, &day, &year);

	if (day < 1 || month < 1 || day > 31 || month > 12) {
		printf("Wrong date!\n");
		return 1;
	}

	printf("%s %d, %d\n", months[month - 1], day, year);

	return 0;
}
