/*
 * Asks user to enter series of words.
 * Empty word to exit.
 * Prints words in sorted order.
*/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// How much bytes to add for realloc.
#define ALLOC_STEP 5LU


// Read characters from input until '\n'. Store them in
// dynamically allocated char array. Return pointer to array.
char *heapReadln(void);

// Compare strings pointed to by ps1 and ps2
int compareCharPP(const void *ps1, const void *ps2);

int main(void)
{
	char **wp;
	char **words = NULL;
	char *new_word = NULL;
	size_t num_words = 0;

	for ( ; ; ) {

		printf("Enter word: ");

		new_word = heapReadln();

		if (strlen(new_word) == 0) {
			free(new_word);
			break;
		}

		words = realloc(words, num_words * sizeof *words + sizeof *words);
		words[num_words++] = new_word;
	}

	qsort(words, num_words, sizeof *words, compareCharPP);

	printf("\nWords in sorted order\n----------\n");

	for (wp = words; wp < words + num_words; wp++) {
		printf("%s\n", *wp);
		free(*wp);
	}

	free(words);
	
	return 0;
}


char *heapReadln(void)
{
	char c;
	char *line;
	char *p;
	size_t chars_read;

	p = line = NULL;
	chars_read = 0;

	for ( ; ; ) {

		if (chars_read % ALLOC_STEP == 0) {
			line = realloc(line, chars_read + ALLOC_STEP);
			p = line + chars_read;
		}

		c = getchar();

		if (c == EOF || c == '\n')
			break;

		*p++ = c;
		chars_read++;
	}

	*p = 0;

	line = realloc(line, strlen(line) + 1);

	return line;
}


int compareCharPP(const void *ps1, const void *ps2)
{
	return strcmp(
		*(char **) ps1,
		*(char **) ps2
	);
}
