/*
 * Program that calculates average word length in a sentence.
*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define MAX_STR_LEN 70


// Computes average word length of a sentence
static double avg_word_len(const char *sentence);


int main(void)
{
	char sentence[MAX_STR_LEN];

	printf("Enter a sentence: ");
	fgets(sentence, sizeof sentence, stdin);
	*(sentence + strlen(sentence) - 1) = 0;

	printf("Average word length: %g\n", avg_word_len(sentence));

	return 0;
}


static double avg_word_len(const char *sentence)
{
	int num_letters = 0, num_words = 0;
	bool in_word = false;

	for ( ; *sentence; sentence++) {
		if (!in_word && isalpha(*sentence)) {
			in_word = true;
			num_words++;
		}
		else if (in_word && !isalpha(*sentence))
			in_word = false;
		if (!in_word)
			continue;
		num_letters++;
	}

	if (num_words)
		return (double) num_letters / num_words;
	return 0;
}
