/*
 * Program that encrypts a message using the Caesar method.
 * 
 * User enters a message and shift amount.
*/


#include <stdio.h>
#include <ctype.h>


#define MAX_SIZE 80
#define NUM_LETTERS 26
#define INPUT_TERMINATOR '\n'


int main(void)
{
	int i;
	int shift;
	char low_letters[NUM_LETTERS], up_letters[NUM_LETTERS];
	char input[MAX_SIZE], output[MAX_SIZE];

	// Populate arrays with alphabet letters
	for (i = 0; i < NUM_LETTERS; i++)
		low_letters[i] = 'a' + (char) i;
	for (i = 0; i < NUM_LETTERS; i++)
		up_letters[i] = 'A' + (char) i;

	printf("Enter a message: ");
	// Store input message
	for (i = 0; i < MAX_SIZE; i++) {
		input[i] = (char) getchar();
		if (input[i] == INPUT_TERMINATOR)
			break;
	}

	printf("Enter shift ammount: ");
	(void)scanf("%d", &shift);

	// Populate output array with encrypted letters
	for (i = 0; i < MAX_SIZE; i++) {
		if (input[i] == INPUT_TERMINATOR) {
			output[i] = input[i];
			break;
		}
		// Encrypt lowercase letter
		else if (
			0 <= input[i] - low_letters[0]
			&& input[i] - low_letters[0] < NUM_LETTERS
		)
		{
			output[i] = (input[i] - low_letters[0] + shift)
				% NUM_LETTERS + low_letters[0];
		}
		// Encrypt uppercase letter
		else if (
			0 <= input[i] - up_letters[0]
			&& input[i] - up_letters[0] < NUM_LETTERS
		)
		{
			output[i] = (input[i] - up_letters[0] + shift)
				% NUM_LETTERS + up_letters[0];
		}
		// Store unencrypted
		else
			output[i] = input[i];
	}

	// Print resulting output
	printf("Encrypted message: ");
	for (i = 0; i < MAX_SIZE; i++) {
		if (output[i] == INPUT_TERMINATOR)
			break;
		else
			putchar(output[i]);
	}

	printf("\n");

	return 0;
}
