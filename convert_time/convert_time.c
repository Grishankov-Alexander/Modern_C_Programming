/*
 * Program that converts 24-hour time to 12-hour time
*/


#include <stdio.h>


int main(void)
{
	int hour, minute;

	printf("Enter a 24-hour time (hh:mm): ");
	(void)scanf("%d :%d", &hour, &minute);

	printf("Equivalent 12-hour time: ");
	if (hour < 12) {
		if (hour == 0)
			printf("12");
		else
			printf("%d", hour);
		printf(":%.2d AM\n", minute);
	} else {
		if (hour == 12)
			printf("12");
		else
			printf("%d", hour - 12);
		printf(":%.2d PM\n", minute);
	}

	return 0;
}
