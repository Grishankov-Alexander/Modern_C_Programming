/*
 * Program that computes scrabble value of a word.
*/


#include <ctype.h>
#include <stdio.h>
#include <string.h>


#define NUM_ELEMENTS(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define WORD_SIZE 20


// Array containing scrabble points for each letter
static const char letter_points['Z' - 'A' + 1] = {
	1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5,
	1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4,
	4, 8, 4, 10
};


// Returns number of scrabble points in a word
static int scrabble_value(const char *word);


int main(void)
{
	char word[WORD_SIZE];

	while (1) {
		printf("Enter scrabble word: (0 to exit) ");
		scanf("%s", word);
		if (strcmp(word, "0") == 0)
			break;
		printf("Scrabble value of %s is %d\n",
			word, scrabble_value(word));
	}

	return 0;
}


static int scrabble_value(const char *word)
{
	int sum = 0;
	char c;

	while (*word) {
		c = toupper(*word);
		if ('A' <= c && c <= 'Z') 
			sum += letter_points[c - 'A'];
		word++;
	}

	return sum;
}
