/*
 * Program that reads an integer entered by the user
 * and converts it to base 8
*/


#include <stdio.h>


int main(void)
{
	int d1, d2, d3, d4, d5;
	int i;

	printf("Enter a number between 0 and 32767: ");
	(void)scanf("%d", &i);

	d5 = i % 8;
	d4 = (i /= 8) % 8;
	d3 = (i /= 8) % 8;
	d2 = (i /= 8) % 8;
	d1 = (i /= 8) % 8;

	printf("In octal, your number is: %d%d%d%d%d\n",
		d1, d2, d3, d4, d5);

	return 0;
}
