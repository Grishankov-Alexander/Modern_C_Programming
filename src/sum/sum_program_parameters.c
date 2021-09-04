/*
 * Program that prints the sum of integers from program parameters
*/


#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	char **p;
	int sum = 0;

	for (p = argv + 1; p < argv + argc; p++)
		sum += atoi(*p);

	printf("Total: %d\n", sum);

	return 0;
}
