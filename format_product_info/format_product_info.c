/*
 * Program that formats product information
 * entered by the user.
*/


#include <stdio.h>


int main(void)
{
	int item_number;
	int month, day, year;
	float unit_price;

	printf("Enter item number: ");
	(void)scanf("%d", &item_number);
	printf("Enter unit price: ");
	(void)scanf("%f", &unit_price);
	printf("Enter purchase date (mm/dd/yyyy): ");
	(void)scanf("%d/%d/%d", &month, &day, &year);

	printf("Item\t\tUnit\t\tPurchase\n");
	printf("\t\tPrice\t\tDate\n");
	printf("%-16d$%7.2f\t%.2d/%.2d/%.4d\n",
		item_number, unit_price,
		month, day, year
	);

	return 0;
}

