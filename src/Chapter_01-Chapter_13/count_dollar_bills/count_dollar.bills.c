/*
 * Program that shows how much bills required
 * to pay for the specified amount
*/

#include <stdio.h>

#define TWENTY_DOLLARS 20
#define TEN_DOLLARS 10
#define FIVE_DOLLARS 5
#define ONE_DOLLAR 1


static void count_bills(int dollars, int *tws, int *tens,
			int *fvs, int *ones);


int main(void)
{
	int twentys;
	int tens;
	int fives;
	int ones;
	int amount;

	printf("Amount of money: ");
	(void)scanf("%d", &amount);

	count_bills(amount, &twentys, &tens, &fives, &ones);

	printf("20$ : %d\n", twentys);
	printf("10$ : %d\n", tens);
	printf("5$ : %d\n", fives);
	printf("1$ : %d\n", ones);

	return 0;
}


static void count_bills(int dollars, int *tws, int *tens,
			int *fvs, int *ones)
{
	*tws = dollars / TWENTY_DOLLARS;
	dollars -= *tws * TWENTY_DOLLARS;
	*tens = dollars / TEN_DOLLARS;
	dollars -= *tens * TEN_DOLLARS;
	*fvs = dollars / FIVE_DOLLARS;
	*ones = dollars -= *fvs * FIVE_DOLLARS;
}
