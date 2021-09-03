/*
 * Program that converts time from 12-hour format to 24-hour format.
*/


#include <stdio.h>
#include <ctype.h>


int main(void)
{
	int h, m;
	char time_suffix, ch;

	printf("Enter a 12-hour time (hh:mm): ");
	scanf("%d :%d %c%c%*c", &h, &m, &time_suffix, &ch);

	if (toupper(time_suffix) != 'A' && toupper(time_suffix) != 'P') {
		printf("Wrong time suffix!\n");
		return 1;
	} else if (toupper(ch) != 'M' && ch != '\n') {
		printf("Wrong time suffix!\n");
		return 1;
	} else if (h == 12) {
		h = toupper(time_suffix) == 'P' ? 12 : 0;
	} else {
		h = toupper(time_suffix) == 'P' ? h + 12 : h;
	}

	printf("Equivalent 24-hour time: %.2d:%.2d\n", h, m);

	return 0;
}
