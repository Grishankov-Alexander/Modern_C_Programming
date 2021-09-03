/*
 * Program that calculates average word length in a sentence.
*/


#include <stdio.h>
#include <stdbool.h>


int main(void)
{
	int letters = 0, words = 0;
	char ch;
	bool count = false;

	printf("Enter a sentence: ");

	while ((ch = getchar()) != '\n') {
		switch (ch) {
			case ' ':
				if (count) {
					count = false;
					words++;
				}
				break;
			default:
				if (!count)
					count = true;
				letters++;
				break;
		}
	}
	if (count)
		count = false, words++;

	printf("Average word length: %.1f\n", (float)letters / words);

	return 0;
}
