/*
 * Classifies a poker hand
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5


static int num_in_rank[NUM_RANKS];
static int num_in_suit[NUM_SUITS];
static bool flush, straight, four, three;
static int pairs;


/* read_cards
 *
 * Reads the cards into external variables;
 * checks for bad cards and duplicate cards;
*/
static void read_cards(void);

/* analyze_hand
 * 
 * Determines whether the hand contains a straight,
 * a flush, four-of-a-kind, three-of-a-kind;
 * Determines the number of pairs
*/
static void analyze_hand(void);

/* print_result
 *
 * Notifies the user of the result
 * using the external variables set by
 * analyze_hand
*/
static void print_result(void);


int main(void)
{
	for ( ; ; ) {
		read_cards();
		analyze_hand();
		print_result();
	}

	return 0;
}


void read_cards(void)
{
	int rank, suit;
	int cards_read = 0;
	char ch, rank_ch, suit_ch;
	bool bad_card;
	bool card_exists[NUM_RANKS][NUM_SUITS];

	printf("\nPoker begins. Specify your hand:\n");
	printf("5s for five spades, tc for ten clubs.\n");
	printf("0 - to exit.\n");

	// Clear\Redefine arrays
	for (rank = 0; rank < NUM_RANKS; rank++) {
		num_in_rank[rank] = 0;
		for (suit = 0; suit < NUM_SUITS; suit++)
			card_exists[rank][suit] = false;
	}
	for (suit = 0; suit < NUM_SUITS; suit++)
		num_in_suit[suit] = 0;

	while (cards_read < NUM_CARDS) {
		bad_card = false;

		printf("Enter a card: ");

		scanf(" %c", &rank_ch);
		switch(tolower(rank_ch)) {
			case '0':	exit(EXIT_SUCCESS);
			case '2':	rank = 0; break;
			case '3':	rank = 1; break;
			case '4':	rank = 2; break;
			case '5':	rank = 3; break;
			case '6':	rank = 4; break;
			case '7':	rank = 5; break;
			case '8':	rank = 6; break;
			case '9':	rank = 7; break;
			case 't':	rank = 8; break;
			case 'j':	rank = 9; break;
			case 'q':	rank = 10; break;
			case 'k':	rank = 11; break;
			case 'a':	rank = 12; break;
			default:	bad_card = true; break;
		}

		scanf(" %c", &suit_ch);
		switch(tolower(suit_ch)) {
			case 'c':	suit = 0; break;
			case 'd':	suit = 1; break;
			case 'h':	suit = 2; break;
			case 's':	suit = 3; break;
			default:	bad_card = false; break;
		}

		while ((ch = getchar()) != '\n')
			if (ch != ' ')
				bad_card = true;

		if (bad_card)
			printf("Bad card; Ignored.\n");
		else if (card_exists[rank][suit])
			printf("Duplicate card; Ignored.\n");
		else {
			card_exists[rank][suit] = true;
			num_in_rank[rank]++;
			num_in_suit[suit]++;
			cards_read++;
		}
	}
}


void analyze_hand(void)
{
	int rank, suit;
	int num_conseq = 0;
	pairs = 0;
	flush = straight = four = three = false; 

	// Find out if it's a flush
	for (suit = 0; suit < NUM_SUITS; suit++)
		if (num_in_suit[suit] == NUM_CARDS)
			flush = true;

	// Find out if it's a straight
	// Skip until number of cards in the rank is not 0
	for (rank = 0; num_in_rank[rank] == 0; rank++)
		;
	// Find how much consecutive ranks are not null
	for ( ; rank < NUM_RANKS && num_in_rank[rank] > 0; num_conseq++, rank++)
		;
	if (num_conseq == NUM_CARDS) {
		straight = true;
		return;
	}

	// Find how much cards of the same rank
	for (rank = 0; rank < NUM_RANKS; rank++)
		switch(num_in_rank[rank]) {
			case 4: four = true; break;
			case 3: three = true; break;
			case 2: pairs++; break;
		}
}


void print_result(void)
{
	if (straight && flush)
		printf("Straight flush");
	else if (four)
		printf("four-of-a-kind");
	else if (three && pairs == 1)
		printf("full house");
	else if (flush)
		printf("flush");
	else if (straight)
		printf("straight");
	else if (three)
		printf("three-of-a-kind");
	else if (pairs == 2)
		printf("two pairs");
	else if (pairs == 1)
		printf("pair");
	else
		printf("high card");

	printf("\n\n");
}
