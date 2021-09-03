/*
 * Program that prints N x N magic square.
 * Values printed vary from 1 to N * N.
*/


#include <stdio.h>


void create_magic_square(int n, int square[n][n]);
void print_magic_square(int n, int square[n][n]);


int main(void)
{
	int n, i, j;

	printf("This program creates a magic square");
	printf(" of a specified size.\n");

	printf("Enter size of magic square: ");
	(void)scanf("%d", &n);

	// Only odd n will create magic square
	if (n % 2 == 0)
		printf("Size should be odd!\nUsing size: %d\n", ++n);

	// Initialize array
	int square[n][n];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			square[i][j] = 0;

	create_magic_square(n, square);

	// Print resulting square
	print_magic_square(n, square);

	return 0;
}


void create_magic_square(int n, int square[n][n])
{
	int i, j;
	int x;
	//int d, div, temp;

	i = 0, j = n / 2, x = 1;

	while (x <= n * n) {
		/*
		// Find how much digits in the x
		for (temp = x, d = 0; temp != 0; ++d)
			temp /= 10;
		// Find divisor for leftmost digit
		for (div = 1; d > 1; d--)
			div *= 10;
		// Put each digit from left to right
		temp = x;
		while (div != 0) {
			putchar(temp / div + '0'); 
			temp %= div;
			div /= 10;
		}
		putchar(' ');
		x++;
		*/
		square[i][j] = x++;

		i = i == 0 ? n - 1 : i - 1;
		j = (j + 1) % n;

		if (square[i][j] != 0) {
			i = (i + 2) % n;
			j = j == 0 ? n - 1 : j - 1;
		}
	}
}


void print_magic_square(int n, int square[n][n])
{
	int i, j;

	printf("Magic square\n");

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%5d", square[i][j]);
		printf("\n");
	}
}
