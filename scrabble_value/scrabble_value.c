/*
 * Program that computes scrabble value of a word.
*/


#include <ctype.h>
#include <stdio.h>


#define NUM_ELEMENTS(x) ((int) (sizeof(x) / sizeof((x)[0])))
int main(void)
{
	const char letter_points['Z' - 'A' + 1] = {
		1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5,
		1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4,
		4, 8, 4, 10
	};
	char c;
	int value = 0;

	printf("Enter a word (0 to exit): ");

	while((c = toupper(getchar())) != '0') {
		if (c == '\n') {
			printf("Scrabble value: %d\n", value);
			printf("Enter a word (0 to exit): ");
			value = 0;
			continue;
		}
		value += letter_points[c - 'A'];
	}

	printf("Scrabble value: %d\n", value);

	return 0;
}
