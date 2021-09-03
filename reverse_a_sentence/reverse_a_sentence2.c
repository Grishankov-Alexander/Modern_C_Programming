/*
 * Program that reverses letters in a sentence using pointers.
*/


#include <stdio.h>


#define SIZE 10


// From last char to first
void reverse_str(char a[], int n);
// Returns size of string that was read
int read_str(char a[], int n);
void print_str(char a[], int n);


int main(void)
{
	int n;
	char sentence[SIZE];

	n = read_str(sentence, SIZE);
	reverse_str(sentence, n);

	print_str(sentence, n);
	
	return 0;
}


void reverse_str(char a[], int n)
{
	char temp, *p = a + n - 1;

	while (a < p)
		temp = *a, *a++ = *p, *p-- = temp;
}


int read_str(char a[], int n)
{
	char c, *p = a;

	printf("Enter sentence: ");

	while (n > 0) {
		c = getchar();
		*p++ = c;
		n--;
		if (c == '\n')
			break;
	}

	return p - a;
}


void print_str(char a[], int n)
{
	while (n > 0)
		putchar(*a++), n--;
	printf("\n");
}
