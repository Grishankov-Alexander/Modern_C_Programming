/*
 * justify.c
 *
 * Removes unnecessary space characters including newlines and tabs.
 * Justifies resulting text and outputs it.
 * Usage: ./justify < unformatted.txt > formatted.txt
*/


#include <string.h>

#include "word.h"
#include "line.h"


#define WORD_SIZE 20


int main(void)
{
	char word[WORD_SIZE + 1] = "";

	for ( ; ; ) {
		read_word(word, sizeof word);
		if (strlen(word) == 0) {
			flush_line();
			return 0;
		} else if ((int) (strlen(word) + 1) > chars_left()) {
			write_justified();
			clear_line();
		}
		add_word(word);
	}
	// get word
	// if word is empty:
		// write line unjustified
		// exit
	// if no space left for word and extra space in the line:
		// write line justified
		// clear line
	// store word in line

	return 0;
}
