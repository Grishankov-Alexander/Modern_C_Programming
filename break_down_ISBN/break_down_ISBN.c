/*
 * Program that breaks down an ISBN entered by the user.
*/


#include <stdio.h>


int main(void)
{
	int gs1, gid, pc, in, cd;

	printf("Enter ISBN: ");
	(void)scanf("%d-%d-%d-%d-%d", &gs1, &gid, &pc, &in, &cd);

	printf("GS1 prefix: %d\n", gs1);
	printf("Group Identifier: %d\n", gid);
	printf("Publisher code: %d\n", pc);
	printf("Item number: %d\n", in);
	printf("Check digit: %d\n", cd);

	return 0;
}

