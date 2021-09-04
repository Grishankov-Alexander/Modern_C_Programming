/*
 * Program that prints command line parameters
 * from last to first
*/


#include <stdio.h>


int main(int argc, char *argv[])
{
	char **p;

	for (p = argv + argc - 1; p > argv; p--)
		printf("%s ", *p);
	printf("\n");

	return 0;
}
