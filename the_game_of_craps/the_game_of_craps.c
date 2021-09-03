/*
 * Program that simulates the game of craps.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


int roll_dice(void);
bool play_game(void);


int main(void)
{
	int num_wins = 0, num_losses = 0;
	bool play_again = true;

	srand((unsigned) time(NULL));

	while (play_again) {

		switch(play_game()) {
			case true:
				printf("You win!\n");
				num_wins++;
				break;
			case false:
				printf("You lose!\n");
				num_losses++;
				break;
		}

		printf("\nPlay again ? ");
		if (tolower(getchar()) != 'y')
			play_again = false;

		while (getchar() != '\n')
			;

		printf("\n");
	}

	printf("Wins: %d\tLosses: %d\n", num_wins, num_losses);

	return 0;
}


int roll_dice(void)
{
	return rand() % 6 + 1 + rand() % 6 + 1;
}


// Return true for win
bool play_game(void)
{
	int point;
	int roll = roll_dice();

	printf("You rolled: %d\n", roll);

	switch (roll) {
		case 7: case 11:
			return true;
		case 2: case 3: case 12:
			return false;
		default:
			point = roll;
			break;
	}

	printf("Your point is %d\n", point);

	for ( ; ; ) {
		roll = roll_dice();
		printf("You rolled: %d\n", roll);
		if (roll == point)
			return true;
		else if (roll == 7)
			return false;
	}
}
