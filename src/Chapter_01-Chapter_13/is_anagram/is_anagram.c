/*
 * Program that checks if two words are anagrams.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


#define NUM_LETTERS 26
#define STRING_SIZE 80
#define INPUT_TERMINATOR '\n'


void read_word(int counts[NUM_LETTERS]);
bool equal_array(int counts1[NUM_LETTERS], int counts2[NUM_LETTERS]);
// Returns true if s1 and s2 are anagrams
bool are_anagrams(const char *s1, const char *s2);
// Reads at most n - 1 characters into s. Excluding newline.
int readln(char *s, int n);


int main(void)
{
	/*
	 * Worked all right but the exercise requires
	 * function to compare 2 strings
	bool anagrams;
	int letter_count1[NUM_LETTERS] = {0};
	int letter_count2[NUM_LETTERS] = {0};

	printf("Enter first word: ");
	read_word(letter_count1);
	printf("Enter second word: ");
	read_word(letter_count2);

	anagrams = equal_array(letter_count1, letter_count2);

	printf("Words are%s anagrams.\n", anagrams ? "" : " not");
	*/

	char s1[STRING_SIZE], s2[STRING_SIZE];

	printf("Enter first word: ");
	readln(s1, sizeof s1);
	printf("Enter second word: ");
	readln(s2, sizeof s2);

	if (are_anagrams(s1, s2))
		printf("Strings are anagrams\n");
	else
		printf("Not anagrams\n");

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


int readln(char *s, int n)
{
	char c, *p;

	for (p = s; n > 1; n--, p++) {
		c = getchar();
		if (c == '\n')
			break;
		*p = c;
	}

	*p = 0;

	return p - s;
}


bool are_anagrams(const char *s1, const char *s2)
{
	int letter_count[NUM_LETTERS] = {0}, *p = letter_count;

	while (*s1) {
		if (isalpha(*s1))
			letter_count[tolower(*s1) - 'a']++;
		s1++;
	}

	while (*s2) {
		if (isalpha(*s2))
			letter_count[tolower(*s2) - 'a']--;
		s2++;
	}

	for ( ; p < letter_count + NUM_LETTERS; p++)
		if (*p)
			return false;

	return true;
}
