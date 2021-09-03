/*
 * This file shows shows interesting examples with pointers
 * and operations on them.
*/


#include <stdio.h>
#include <string.h>


#define NUM_ROWS 2
#define NUM_COLUMNS 3


static void inspect_2dim_array(void);
static void inspect_argv(int argc, char **argv);


int main(int argc, char **argv)
{
	printf("argc = %d\n", argc);

	inspect_2dim_array();

	inspect_argv(argc, argv);

	return 0;
}


void inspect_2dim_array(void)
{
	int i, j, n;
	int a[NUM_ROWS][NUM_COLUMNS];
	int *p;
	int (*q)[NUM_COLUMNS];

	// Initialize a with numbers
	for (i = 0, n = 0; i < NUM_ROWS; i++)
		for (j = 0; j < NUM_COLUMNS; j++)
			a[i][j] = n++;

	// Pointer way to initialize all alements of row i
	i = 1;
	for (p = *(a + i); p < *(a + i) + NUM_COLUMNS; p++)
		*p = n++;

	// Pointer way to initialize all elements of column j
	j = 1;
	for (i = 0; i < NUM_ROWS; i++)
		*(*(a + i) + j) = n++;
	//  Pretty much the same as
	for (q = a; q < a + NUM_ROWS; q++)
		(*q)[j] = --n;


	printf("\nArray under inspection:\n");
	printf("int a[%d][%d] (Same as int (*a)[%d])\n\n",
		NUM_ROWS, NUM_COLUMNS, NUM_COLUMNS);

	// Print value for each element
	for (i = 0; i < NUM_ROWS; i++)
		for (j = 0; j < NUM_COLUMNS; j++)
			printf("a[%d][%d] = %d\n", i, j, a[i][j]);

	printf("\n");

	// Print address for each element
	for (i = 0; i < NUM_ROWS; i++)
		for (j = 0; j < NUM_COLUMNS; j++)
			printf("&a[%d][%d] = %p\n", i, j, (void *) &a[i][j]);

	// Print a[0]
	printf("\na[0] = %p\n", (void *) a[0]);
	// Print a[1]
	printf("a[1] = %p\n", (void *) a[1]);

	// Print &a[0]
	printf("\n&a[0] = %p\n", (void *) &a[0]);
	// Print &a[1]
	printf("&a[1] = %p\n", (void *) &a[1]);

	// Print value of a
	printf("\na = %p\n", (void *) a);
	// Print address of a
	printf("&a = %p\n", (void *) &a);

	// Print the result of a + 0
	printf("\na + 0 = %p\n", (void *) (a + 0));
	// Print the result of a + 1
	printf("a + 1 = %p\n", (void *) (a + 1));

	// Print the result of *a + 0
	printf("\n*a + 0 = %p\n", (void *) (*a + 0));
	// Print the result of *a + 1
	printf("*a + 1 = %p\n", (void *) (*a + 1));
	// Print the result of *a + 3
	printf("*a + 3 = %p\n", (void *) (*a + 3));

	// Print the result of *(a + 0) + 1
	printf("\n*(a + 0) + 1 = %p\n", (void *) (*(a + 0) + 1));
	// Print the result of *(a + 1) + 1
	printf("*(a + 1) + 1 = %p\n", (void *) (*(a + 1) + 1));

	// Print the result of *(*(a + 0) + 1)
	printf("\n*(*(a + 0) + 1) = %d\n", *(*(a + 0) + 1));
	// Print the result of *(*(a + 0) + 1)
	printf("*(*(a + 1) + 1) = %d\n", *(*(a + 1) + 1));

	// Print the result of *(a[0] + 1)
	printf("\n*(a[0] + 1) = %d\n", *(a[0] + 1));
	// Print the result of *(a[0] + 1)
	printf("*(a[1] + 1) = %d\n", *(a[1] + 1));

	printf("\n");
}


void inspect_argv(int argc, char **argv)
{
	int i, j, r, col;
	char *c;

	// Print value of argc
	printf("\nargc = %d\n", argc);

	// Add 1 to every char of row r
	r = 0;
	for (c = *(argv + r); *c != 0; c++)
		*c += 1;

	// Subtract 1 to every char in column col
	col = 1;
	for (i = 0; i < argc; i++)
		if ((unsigned) col < strlen(argv[i]))
			*(argv[i] + col) -= 1;
	// Pretty much the same as
	for (char **q = argv; q < argv + argc; q++)
		if ((unsigned) col < strlen(*q))
			(*q)[col] += 1;

	// Print values of argv
	printf("argv = ");
	for (i = 0; i < argc; i++) {
		printf("\"");
		for (j = 0; argv[i][j] != 0; j++)
			putchar(argv[i][j]);
		printf("\" ");
	}

	// Print values for each char
	printf("\n\n");
	for (i = 0; i < argc; i++) {
		for (j = 0; argv[i][j] != 0; j++)
			printf("argv[%d][%d] = %c\n", i, j, argv[i][j]);
		printf("argv[%d][%d] = \\0\n\n", i, j);
	}

	// Print addresses for each char
	printf("\n");
	for (i = 0; i < argc; i++) {
		for (j = 0; argv[i][j] != 0; j++)
			printf("&argv[%d][%d] = %p\n", i, j, (void *) &argv[i][j]);
		printf("&argv[%d][%d] = %p\n\n", i, j, (void *) &argv[i][j]);
	}

	// Print values for argv[i]
	printf("\n");
	for (i = 0; i < argc; i++)
		printf("argv[%d] = %p\n", i, (void *) argv[i]);
	// Print addresses for argv[i]
	printf("\n");
	for (i = 0; i < argc; i++)
		printf("&argv[%d] = %p\n", i, (void *) &argv[i]);

	// Print value of argv
	printf("\nargv = %p\n", (void *) argv);
	// Print address of argv
	printf("&argv = %p\n", (void *) &argv);

	// Print value of argv + 1
	printf("\nargv + 1 = %p\n", (void *) (argv + 1));
	// Print value of *argv
	printf("*argv = %p\n", (void *) *argv);
	// Print value of *(argv + 1)
	printf("*(argv + 1) = %p\n", (void *) *(argv + 1));
	// Print value of *(*(argv + 0) + 1)
	printf("*(*(argv + 0) + 2) = %c\n", *(*(argv + 0) + 2));

	printf("\n");
}
