/*
 * Program the prints words in a sentence from last to first.
*/


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_SIZE 1024
#define NUM_WORDS 30
#define MAX_WORD_SIZE 20


static char terminator = '.';


// Reads at most n - 1 characters from stdin into a
static int read_str(char *a, int n);
// Last word will become first and first will become last, etc...
static void print_reversed_words(char *a, int n);
// Returns number of words read into 2-dim char array
static int read_words(char (*a)[]);


int main(void)
{
	/* Works all right but author wants
	 * us to rewrite the program so it
	 * stores words int char *[]
	int n;
	char a[MAX_SIZE];

	n = read_str(a, MAX_SIZE);
	
	print_reversed_words(a, n);
	*/

	char words[NUM_WORDS][MAX_WORD_SIZE], (*p)[MAX_WORD_SIZE];
	int n;

	n = read_words(words);

	printf("Reversed:");

	for (p = words + n - 1; words <= p; p--)
		printf(" %s", *p);

	printf("\n");

	return 0;
}


int read_str(char *a, int n)
{
	char c, *p;

	printf("Enter your message: ");

	for (p = a; p < a + n - 1; p++) {
		c = getchar();
		if (c == '.' || c == '!' || c == '?') {
			terminator = c;
			break;
		}
		*p = c;
	}

	*p = 0;

	return p - a;
}


static void print_reversed_words(char *a, int n)
{
	char *p;
	int word_length;

	for (p = a + n - 1; a < p; p--) {
		// Point p to the space
		if (*p != ' ')
			continue;

		// Calculate word length including space
		word_length = a + n - p;

		// Readjust n by subtracting length of word
		n -= word_length;

		// Print the word
		for (p = p + 1; word_length > 1; p++, word_length--)
			putchar(*p);

		// Put space
		putchar(' ');

		// Readjust p
		p = a + n;
	}

	// Put the remaining word
	for (p = a; p < a + n; p++)
		putchar(*p);

	// Put the terminating char
	printf("%c\n", terminator);
}


static int read_words(char (*a)[MAX_WORD_SIZE])
{
	char (*p)[MAX_WORD_SIZE], *q, c;
	bool in_word;

	printf("Enter message: ");

	for (p = a; p < a + NUM_WORDS; p++) {
		in_word = false;
		for (q = *p; q < *p + MAX_WORD_SIZE; ) {
			c = getchar();
			if (c == '\n') {
				*q = 0;
				if (in_word)
					return p + 1 - a;
				return p - a;
			}
			else if (!in_word && isalpha(c))
				in_word = true;
			else if (in_word && !isalpha(c))
				break;
			if (in_word)
				*q++ = c;
		}
		// q went out of bounds before word was read
		if (q == *p + MAX_WORD_SIZE)
			q--;
		*q = 0;
	}

	return p - a;
}
