/*
 * Definitions for working with output lines
*/


#include <string.h>
#include <stdio.h>

#include "line.h"


static char line[LINE_SIZE + 1] = "";
static int num_chars = 0;
static int num_words = 0;


int chars_left(void)
{
	return LINE_SIZE - num_chars;
}


char *clear_line(void)
{
	strcpy(line, "");
	num_chars = num_words = 0;
	return line;
}


char *add_word(char *word)
{
	if(num_words > 0) {
		line[num_chars++] = ' ';
		line[num_chars] = 0;
	}
	strcat(line, word);
	num_chars += strlen(word);
	num_words++;
	return line;
}


void write_justified(void)
{
	int i, j;
	int num_spaces;
	int num_extra = chars_left();
	for (i = 0; i < num_chars; i++) {
		if (line[i] != ' ') {
			putchar(line[i]);
			continue;
		}
		num_words--;
		// + 1 for the space that already exists
		num_spaces = num_extra / num_words;
		for (j = 0; j <= num_spaces; j++)
			putchar(' ');
		num_extra -= num_spaces;
	}
	putchar('\n');
}


void flush_line(void)
{
	fputs(line, stdout);
}
