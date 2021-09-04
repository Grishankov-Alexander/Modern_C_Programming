/*
 * Classifies a poker hand
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>


#define NUM_CARDS 5
#define NUM_RANKS 13
#define NUM_SUITS 4


static bool straight, flush, royal, four, three;
static int pairs;


/* Generate random hand.
 * hand[0][0] - rank of the first card.
 * hand[0][1] - suit.
*/
static void generate_hand(int hand[][2]);
/* Sets global variables depending on the hand */
static void analyze_hand(int hand[][2]);
/* Analyzes global variables and prints overall outcome */
static void print_result(int hand[][2]);


int main(void)
{
	// hand[0][0] - stores rank
	// hand[0][1] - stores suit
	int hand[NUM_CARDS][2];
	char command;

	srand((unsigned) time(NULL));

	for ( ; ; ) {
		printf("\n\nWelcome to poker hand analyzer!\n");
		printf("\tRules are simple: Program randomly\n");
		printf("\tgenerates your hand.\n");
		printf("\tAfter that, it prints you your score.\n");
		printf("Commands: 1 - generate hand; 0 - exit\n");
		printf("Enter the command: ");

		scanf(" %c", &command);
		
		switch (command) {
			case '1':
				generate_hand(hand);
				analyze_hand(hand);
				print_result(hand);
				break;
			case '0':
				return 0;
			default:
				continue;
		}
	}
}


void generate_hand(int hand[][2])
{
	int i, j;
	int rank, suit;
	int tmp;
	bool skip;

	// Reset the hand
	for (i = 0; i < NUM_CARDS; i++)
		for (j = 0; j < 2; j++)
			hand[i][j] = 0;

	for (i = j = 0; i < NUM_CARDS; i++) {
		skip = false;
		rank = rand() % NUM_RANKS;
		suit = rand() % NUM_SUITS;
		// Skip card if already exists
		for (tmp = 0; tmp < i; tmp++)
			if (rank == hand[tmp][j] && suit == hand[tmp][j + 1])
				skip = true;
		if (skip) {
			i--;
			continue;
		}

		hand[i][j] = rank;
		hand[i][j + 1] = suit;
	}
}


void analyze_hand(int hand[][2])
{
	int i, j;
	int tmp, num_conseq_rank, num_rank_seen;

	// Clear global vars
	royal = straight = four = three = false;
	flush = true;
	pairs = 0;

	// Check for "straight"
	for (i = j = 0, tmp = hand[i][j]; i < NUM_CARDS; i++)
		if (hand[i][j] < tmp)
			tmp = hand[i][j];
	for (i = 0, num_conseq_rank = 1; i < NUM_CARDS; i++)
		if (hand[i][j] == tmp + 1) {
			tmp = hand[i][j];
			num_conseq_rank++;
			i = -1;
		}
	// Check for ace, 2, 3, 4, 5
	if (tmp == 5 && num_conseq_rank == NUM_CARDS - 1)
		for (i = 0; i < NUM_CARDS; i++)
			if (hand[i][j] == NUM_RANKS - 1)
				num_conseq_rank++;

	if (num_conseq_rank == NUM_CARDS)
		straight = true;

	// Check for "Flush"
	for (i = j = 1; i < NUM_CARDS; i++)
		if (hand[i][j] != hand[i - 1][j])
			flush = false;

	// Check for royal flush (ace is the last rank)
	if (straight && flush && tmp == NUM_RANKS - 1)
		royal = true;

	// Check how much times each rank has been seen
	// P.S. tmp will serve indexing purpose here
	for (i = j = 0; i < NUM_CARDS; i++) {
		num_rank_seen = 1;
		for (tmp = 0; tmp < i; tmp++)
			if (hand[i][j] == hand[tmp][j])
				break;
		// tmp == i if rank is seen for the first time
		if (tmp != i)
			continue;
		for (tmp = i + 1; tmp < NUM_CARDS; tmp++)
			if (hand[i][j] == hand[tmp][j])
				num_rank_seen++;
		switch (num_rank_seen) {
			case 2:	pairs++; break;
			case 3:	three = true; break;
			case 4:	four = true; break;
		}
	}
}


void print_result(int hand[][2])
{
	int i, j;
	char c;

	printf("Generated hand:");

	for (i = j = 0; i < NUM_CARDS; i++, j = 0) {
		switch (hand[i][j]) {
			case 0:		c = '2'; break;
			case 1:		c = '3'; break;
			case 2:		c = '4'; break;
			case 3:		c = '5'; break;
			case 4:		c = '6'; break;
			case 5:		c = '7'; break;
			case 6:		c = '8'; break;
			case 7:		c = '9'; break;
			case 8:		c = 't'; break;
			case 9:		c = 'j'; break;
			case 10:	c = 'q'; break;
			case 11:	c = 'k'; break;
			case 12:	c = 'a'; break;
			default:	c = '?'; break;
		}

		printf(" %c", c);
		j++;

		switch (hand[i][j]) {
			case 0:		c = 'c'; break;
			case 1:		c = 'd'; break;
			case 2:		c = 'h'; break;
			case 3:		c = 's'; break;
		}
		putchar(c);
	}

	printf("\nYour hand scored: ");

	if (royal)			printf("royal flush");
	else if (straight && flush)	printf("straight flush");
	else if (four)			printf("four-of-a-kind");
	else if (three && pairs == 1)	printf("full house");
	else if (flush)			printf("flush");
	else if (straight)		printf("straight");
	else if (three)			printf("three-of-a-kind");
	else if (pairs == 2)		printf("two pairs");
	else if (pairs == 1)		printf("pair");
	else				printf("high card");

	printf("\n");
}
