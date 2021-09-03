/*
 * Program the prints words in a sentence from last to first.
*/


#include <stdio.h>
#include <stdbool.h>


#define MAX_SIZE 1024


static char terminator = '.';


// Returns number of characters read into array a of size n
static int read_str(char *a, int n);
// Last word will become first and first will become last, etc...
static void print_reversed_words(char *a, int n);


int main(void)
{
	int n;
	char a[MAX_SIZE];

	n = read_str(a, MAX_SIZE);
	
	print_reversed_words(a, n);

	return 0;
}


int read_str(char *a, int n)
{
	char c, *p;

	printf("Enter your message: ");

	for (p = a; p < a + n; p++) {
		c = getchar();
		if (c == '.' || c == '!' || c == '?') {
			terminator = c;
			break;
		}
		*p = c;
	}

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
