/*
 * Program that counts a number of vowels in the sentence.
*/


#include <stdio.h>
#include <ctype.h>


#define MAX_SENTENCE_SIZE 70
static int count_vowels(const char *sentence);


int main(void)
{
	char sentence[MAX_SENTENCE_SIZE];

	printf("Enter a sentence: ");
	fgets(sentence, sizeof sentence, stdin);

	printf("Your sentence contains %d vowels.\n", count_vowels(sentence));

	return 0;
}


static int count_vowels(const char *sentence)
{
	int n = 0;

	while (*sentence) {
		switch(tolower(*sentence++)) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				n++;
				break;
		}
	}

	return n;
}
