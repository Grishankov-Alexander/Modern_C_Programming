/*
 * Displays entered number using seven-segment display.
*/


#include <stdio.h>


#define MAX_DIGITS 10
#define NUM_DIGITS 10
#define NUM_SEGMENTS 7
// How much rows, columns 7-segment display takes
#define NUM_ROWS 3
#define NUM_COLUMNS 3
#define TOTAL_COLUMNS (NUM_COLUMNS * MAX_DIGITS)


// What segments should be filled for each digit on 7-segment display
static int segments[NUM_DIGITS][NUM_ROWS * NUM_COLUMNS] = {
	{0,1,0,1,0,1,1,1,1},
	{0,0,0,0,0,1,0,0,1},
	{0,1,0,0,1,1,1,1,0},
	{0,1,0,0,1,1,0,1,1},
	{0,0,0,1,1,1,0,0,1},
	{0,1,0,1,1,0,0,1,1},
	{0,1,0,1,1,0,1,1,1},
	{0,1,0,0,0,1,0,0,1},
	{0,1,0,1,1,1,1,1,1},
	{0,1,0,1,1,1,0,1,1}
};
// characters to be printed for numbers entered.
static char digits[NUM_ROWS][TOTAL_COLUMNS];


static void clear_digits(void);
void store_digit(int digit, int position);
void print_digits(void);


int main(void)
{
	int pos = 0;
	char ch;

	printf("Enter a number: ");

	clear_digits();

	while ((ch = getchar()) != '\n' && pos < MAX_DIGITS)
		if ('0' <= ch && ch <= '9')
			store_digit(ch - '0', pos++);

	print_digits();
}


static void clear_digits(void)
{
	int i, j;

	for (i = 0; i < NUM_ROWS; i++)
		for (j = 0; j < TOTAL_COLUMNS; j++)
			digits[i][j] = '\0';
}


void store_digit(int digit, int position)
{
	int i, j;

	if (position >= MAX_DIGITS) {
		printf("Ignored; max position = %d\n", MAX_DIGITS - 1);
		return;
	}

	// 7-segment representation needs more than one row
	position = NUM_COLUMNS * position;

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLUMNS; j++, position++) {
			if (segments[digit][i * NUM_ROWS + j] == 0) {
				digits[i][position] = ' ';
				continue;
			}
			digits[i][position] = j == 1 ? '_' : '|';
		}
		position -= NUM_COLUMNS;
	}
}


void print_digits(void)
{
	int i, j;

	printf("\n");

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < TOTAL_COLUMNS; j++) {
			if (j % NUM_COLUMNS == 0)
				putchar(' ');
			putchar(digits[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
