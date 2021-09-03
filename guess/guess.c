/*
 * Asks user to guess a hidden number
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


#define MAX_NUM 100


int new_secret(void);
void read_guesses(int secret);


int main(void)
{
	char command;
	int secret;

	srand((unsigned) time(NULL));

	printf("Guess the secret number between 1 and %d.\n\n", MAX_NUM);

	do {
		secret = new_secret();
		printf("A new number has been chosen.\n");
		read_guesses(secret);
		printf("\nPlay again? (Y/N) ");
		scanf(" %c", &command);
		printf("\n");
	} while (tolower(command) == 'y');

	return 0;
}


int new_secret(void)
{
	return rand() % MAX_NUM + 1;
}


void read_guesses(int secret)
{
	int guess, num_guesses = 0;
	
	for ( ; ; ) {
		num_guesses++;
		printf("Your guess is: ");
		scanf("%d", &guess);

		if (guess == secret) {
			printf("You won in %d guesses!\n", num_guesses);
			return;
		} else if (guess < secret)
			printf("Too low; try again.\n");
		else
			printf("Too high; try again.\n");
	}
}
