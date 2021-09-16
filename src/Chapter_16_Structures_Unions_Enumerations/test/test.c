/*
 * File for outlining concepts from the chapter.
*/


#include <stdio.h>


#define PRINT_TOPIC(name) printf("\n\n" #name "\n----------\n")
#define SIZE 30


int main(void)
{
	// Structures
	{
		PRINT_TOPIC(structures);

		// Declaring and defining
		struct item {
			int part_n;
			char *name;
			int in_hand;
		}
			hdd = {228, "Hard Disk Drive", 13},
			/* C99 Feature */
			ssd = {.part_n = 229, "Solid State Drive", .in_hand = 9},
			videocard = {.part_n = 230, .in_hand = 1 },
			dummy1 = {0},
			dummy2 = {0};

		printf("Total in_hand: %d\n",
			hdd.in_hand + ssd.in_hand + videocard.in_hand);

		// Accessing a member and assignments
		dummy1.part_n = videocard.part_n + 1;
		dummy1.name = "dummy part 1";
		dummy1.in_hand = 666;
		// This assignment can be used for copying arrays
		dummy2 = dummy1;
		printf("dummy2.name = %s\n", dummy2.name);

		// Let us clarify that array copying can succeed
		struct { int arr[SIZE]; } a1 = {{[0] = 1, 2, 3}}, a2;
		a2 = a1;
		a2.arr[0] = 4;
		for (int i = 0; i < 3; i++)
			printf("a1.arr[%d] = %d\t", i, a1.arr[i]);
		printf("\n");
		for (int i = 0; i < 3; i++)
			printf("a2.arr[%d] = %d\t", i, a2.arr[i]);
		printf("\n");

		// Another Topic
	}

	return 0;
}
