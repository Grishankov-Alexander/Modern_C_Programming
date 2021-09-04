/*
 * Program that converts numerical grade to Letter
*/


#include <stdio.h>


int main(void)
{
	int grade;
	int tenths;

	printf("Enter numerical grade: ");
	(void)scanf("%d", &grade);

	tenths = grade > 100 || grade < 0 ? -1 : grade / 10;

	printf("Letter grade: ");
	switch (tenths) {
		case 0: case 1: case 2: case 3: case 4: case 5:
			printf("F");
			break;
		case 6:
			printf("D");
			break;
		case 7:
			printf("C");
			break;
		case 8:
			printf("B");
			break;
		case 9: case 10:
			printf("A");
			break;
		default:
			printf("\rError: Wrong grade entered!");
			break;
	}
	printf("\n");

	return 0;
}
