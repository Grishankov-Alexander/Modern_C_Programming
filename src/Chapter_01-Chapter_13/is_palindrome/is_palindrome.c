/*
 * Checks whether a message readen is a palindrome
 * (The letters in the message are the same
 * from left to right and from right to left).
*/


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


#define SIZE 100


bool is_palindrome(char a[], int n);
// Return number of characters read
int read_message(char a[], int n);


int main(void)
{
	char a[SIZE];
	int n;

	n = read_message(a, SIZE);

	if (is_palindrome(a, n))
		printf("Palindrome.\n");
	else
		printf("Not a palindrome.\n");

	return 0;
}


bool is_palindrome(char a[], int n)
{
	char *p = a + n - 1;

	while (a < p) {
		if (!isalpha(*a)) {
			a++;
			continue;
		} else if (!isalpha(*p)) {
			p--;
			continue;
		} else if (tolower(*a) != tolower(*p))
			return false;
		a++, p--;
	}

	return true;
}


int read_message(char a[], int n)
{
	char c, *p = a;

	printf("Enter a message: ");

	while (n > 0) {
		c = getchar();
		*p++ = c;
		n--;
		if (c == '\n')
			break;
	}

	return p - a;
}
