/*
 * Program that randomly walks across a 10x10 array.
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


// Available number of moves
#define NUM_MOVES 4
#define GO_UP 0
#define GO_RIGHT 1
#define GO_DOWN 2
#define GO_LEFT 3

// Array properties
#define NUM_ROWS 10
#define NUM_COLUMNS 10
#define NUM_EL(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define INIT_CHAR '.'


void gen_random_walk(char a[NUM_ROWS][NUM_COLUMNS]);
void print_array(char a[NUM_ROWS][NUM_COLUMNS]);


int main(void)
{
	char a[NUM_ROWS][NUM_COLUMNS];
	int i, j;

	// Seed random number generator
	srand((unsigned) time(NULL));

	// Initialize array
	for (i = 0; i < NUM_ROWS; i++)
		for (j = 0; j < NUM_COLUMNS; j++)
			a[i][j] = INIT_CHAR;

	gen_random_walk(a);

	// Print the resulting array
	print_array(a);

	return 0;
}


void gen_random_walk(char a[NUM_ROWS][NUM_COLUMNS])
{
	char c = 'A';
	int i, j, next_i, next_j;
	int move;
	bool tried_all_moves = false;
	bool tried_move[NUM_MOVES] = {false};

	// Pick the initial spot
	next_i = i = rand() % NUM_ROWS;
	next_j = j = rand() % NUM_COLUMNS;
	a[i][j] = c++;

	while (!tried_all_moves && c <= 'Z') {
		// Generate new move
		move = rand() % NUM_MOVES;

		// If this move was tried before
		if (tried_move[move]) {
			// Check that not all moves have been tried
			for (move = 0; move < NUM_MOVES; move++) {
				if (!tried_move[move])
					break;
				else if (move == NUM_MOVES - 1)
					tried_all_moves = true;
			}
			// Go to generating new move if not all moves
			// have been tried
			continue;
		}

		// Find array coordinates for the move
		switch (move) {
			case GO_UP:
				next_i = i - 1;
				next_j = j;
				break;
			case GO_RIGHT:
				next_i = i;
				next_j = j + 1;
				break;
			case GO_DOWN:
				next_i = i + 1;
				next_j = j;
				break;
			case GO_LEFT:
				next_i = i;
				next_j = j - 1;
				break;
		}

		// If index is out of boundary, or array already has a letter
		// indicate that this move was attempted and go back to generating
		// new move.
		if (next_i < 0 || next_i >= NUM_ROWS
			|| next_j < 0 || next_j >= NUM_COLUMNS
			|| a[next_i][next_j] != INIT_CHAR) {
			tried_move[move] = true;
			continue;
		}

		// All tests had passed. We can put
		// new letter into chosen coordinates.
		i = next_i, j = next_j;
		a[i][j] = c++;

		// Reset tried moves
		for (move = 0; move < NUM_MOVES; move++)
			tried_move[move] = false;
	}
}



void print_array(char a[NUM_ROWS][NUM_COLUMNS])
{
	int i, j;

	printf("\nRandow walk\n");
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLUMNS; j++)
			printf(" %c", a[i][j]);
		printf("\n");
	}
}
