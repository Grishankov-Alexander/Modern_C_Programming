/*
 * Program that checks if two words are anagrams.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


#define NUM_LETTERS 26
#define INPUT_TERMINATOR '\n'


void read_word(int counts[NUM_LETTERS]);
bool equal_array(int counts1[NUM_LETTERS], int counts2[NUM_LETTERS]);


int main(void)
{
	bool anagrams;
	int letter_count1[NUM_LETTERS] = {0};
	int letter_count2[NUM_LETTERS] = {0};

	printf("Enter first word: ");
	read_word(letter_count1);
	printf("Enter second word: ");
	read_word(letter_count2);

	anagrams = equal_array(letter_count1, letter_count2);

	printf("Words are%s anagrams.\n", anagrams ? "" : " not");

	return 0;
}


void read_word(int counts[NUM_LETTERS])
{
	int c;

	while ((c = tolower(getchar())) != INPUT_TERMINATOR)
		if (isalpha(c))
			counts[c - 'a']++;
}


bool equal_array(int counts1[NUM_LETTERS], int counts2[NUM_LETTERS])
{
	int i;

	for (i = 0; i < NUM_LETTERS; i++)
		if (counts1[i] != counts2[i])
			return false;

	return true;
}
