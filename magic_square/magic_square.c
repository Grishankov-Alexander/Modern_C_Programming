/*
 * Program that asks the user to enter 16 numbers
 * from 1 to 16 and then displays them in a 4*4 square.
 * Also it displays the sums of columns, rows
 * and diagonals. If sums are the same, it's said to be
 * a magic square.
*/


#include <stdio.h>


int main(void)
{
	int one_one, one_two, one_three, one_four;
	int two_one, two_two, two_three, two_four;
	int three_one, three_two, three_three, three_four;
	int four_one, four_two, four_three, four_four;
	int row_sum_one, row_sum_two, row_sum_three, row_sum_four;
	int column_sum_one, column_sum_two, column_sum_three, column_sum_four;
	int diag_sum_one, diag_sum_two;


	printf("Enter the numbers from 1 to 16 in any order:\n");
	(void)scanf(
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		&one_one, &one_two, &one_three, &one_four,
		&two_one, &two_two, &two_three, &two_four,
		&three_one, &three_two, &three_three, &three_four,
		&four_one, &four_two, &four_three, &four_four
		);

	row_sum_one = one_one + one_two + one_three + one_four;
	row_sum_two = two_one + two_two + two_three + two_four;
	row_sum_three = three_one + three_two + three_three + three_four;
	row_sum_four = four_one + four_two + four_three + four_four;

	column_sum_one = one_one + two_one + three_one + four_one;
	column_sum_two = one_two + two_two + three_two + four_two;
	column_sum_three = one_three + two_three + three_three + four_three;
	column_sum_four = one_four + two_four + three_four + four_four;

	diag_sum_one = one_one + two_two + three_three + four_four;
	diag_sum_two = four_one + three_two + two_three + one_four;

	printf("\n%2d %2d %2d %2d\n", one_one, one_two, one_three, one_four);
	printf("%2d %2d %2d %2d\n", two_one, two_two, two_three, two_four);
	printf("%2d %2d %2d %2d\n", three_one, three_two, three_three, three_four);
	printf("%2d %2d %2d %2d\n\n", four_one, four_two, four_three, four_four);

	printf("Row sums: %d %d %d %d\n", row_sum_one,
		row_sum_two, row_sum_three, row_sum_four);
	printf("Column sums: %d %d %d %d\n", column_sum_one,
		column_sum_two, column_sum_three, column_sum_four);
	printf("Diagonal sums: %d %d\n", diag_sum_one, diag_sum_two);
	
	return 0;
}

