/*
 * Program that converts number (xxx) xxx-xxxx
 * to xxx.xxx.xxxx
*/


#include <stdio.h>


int main(void)
{
	int first_triad, second_triad, quartet;

	printf("Enter phone number [(xxx) xxx-xxxx]: ");
	(void)scanf("(%d) %d-%d", &first_triad, &second_triad,
			&quartet);

	printf("You entered: %d.%d.%d\n", first_triad,
			second_triad, quartet);

	return 0;
}

