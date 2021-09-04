/*
 * Deals a random hand of cards
*/


#include <stdio.h>
#include <stdlib.h>    // srand, rand
#include <time.h>
#include <stdbool.h>


#define NUM_SUITS 4
#define NUM_RANKS 13


int main(void)
{
	bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
	int suit, rank, num_cards;

	const char *suits[] = {
		"clubs", "spades", "diamonds", "hearts"
	};
	const char *ranks[] = {
		"Two", "Three", "Four", "Five",
		"Six", "Seven", "Eigth", "Nine",
		"Ten", "Jack", "Queen", "King",
		"Ace"
	}; 

	srand((unsigned) time(NULL));
	printf("Enter number of cards in hand: ");
	(void)scanf("%d", &num_cards);
	printf("----" "Your hand" "----\n");

	while (num_cards > 0) {
		suit = rand() % NUM_SUITS;
		rank = rand() % NUM_RANKS;
		if (!in_hand[suit][rank]) {
			in_hand[suit][rank] = true;
			num_cards--;
			printf("%s of %s\n", ranks[rank], suits[suit]);
		}
	}

	return 0;
}
