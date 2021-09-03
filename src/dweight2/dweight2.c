/*
 * Computes the dimensional weight of the box
 * which dimensions are provided by user input
*/

#include <stdio.h>

#define INCHES_PER_POUND 166

int main(void) {
	int width, height, length, volume, weight;

	printf("Enter width of box: ");
	(void)scanf("%d", &width);
	printf("Enter height of box: ");
	(void)scanf("%d", &height);
	printf("Enter length of box: ");
	(void)scanf("%d", &length);
	volume = width * height * length;
	weight = (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND;

	printf("Volume of the box (cubic inches): %d\n", volume);
	printf("Dimensional weight (pounds): %d\n", weight);

	return 0;
}
