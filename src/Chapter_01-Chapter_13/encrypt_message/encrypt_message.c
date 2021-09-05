/*
 * Program that encrypts a message using the Caesar method.
 * 
 * User enters a message and shift amount.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


#define MAX_SIZE 80
#define NUM_LETTERS 26


static char *encrypt_caesar(char *msg, int shift);


int main(void)
{
	char msg[MAX_SIZE];
	int shift;

	printf("Enter message to be encrypted: ");
	fgets(msg, sizeof msg, stdin);
	// Get rid of \n
	if (strlen(msg))
		*(msg + strlen(msg) - 1) = 0;
	printf("Enter shift value: ");
	scanf("%d", &shift);

	printf("Caesar encrypted message: %s\n", encrypt_caesar(msg, shift));

	return 0;
}


static char *encrypt_caesar(char *msg, int shift)
{
	char *p;
	bool is_lower;
	int shifted_val;

	for (p = msg; *p; p++) {
		is_lower = false;
		// Continue if *p isn't a letter
		if (!isalpha(*p))
			continue;
		// Determine if *p is uppercase or lowercase
		else if (*p == tolower(*p))
			is_lower = true;
		shifted_val = (is_lower ? *p - 'a' : *p - 'A') + shift;
		shifted_val %= NUM_LETTERS;
		if (shifted_val < 0)
			shifted_val += NUM_LETTERS;
		*p = is_lower ? shifted_val + 'a' : shifted_val + 'A';
	}

	return msg;
}
