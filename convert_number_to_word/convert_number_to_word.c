/*
 * Program that asks for a 2-digit number
 * and converts it to word
*/


#include <stdio.h>


int main(void)
{
	int ones, tenths;

	printf("Enter a dwo-digit number: ");
	scanf("%1d%1d", &tenths, &ones);

	switch (tenths) {
		case 2: printf("twenty"); break;
		case 3: printf("thirty"); break;
		case 4: printf("fourty"); break;
		case 5: printf("fifty"); break;
		case 6: printf("sixty"); break;
		case 7: printf("seventy"); break;
		case 8: printf("eighty"); break;
		case 9: printf("ninety"); break;
	}

	if (tenths != 1) {
		if (ones && tenths != 0) printf("-");
		switch (ones) {
			case 1: printf("one"); break;
			case 2: printf("two"); break;
			case 3: printf("three"); break;
			case 4: printf("four"); break;
			case 5: printf("five"); break;
			case 6: printf("six"); break;
			case 7: printf("seven"); break;
			case 8: printf("eight"); break;
			case 9: printf("nine"); break;
		}
	} else {
		switch (ones) {
			case 0: printf("ten"); break;
			case 1: printf("eleven"); break;
			case 2: printf("twelve"); break;
			case 3: printf("thirteen"); break;
			case 4: printf("fourteen"); break;
			case 5: printf("fifteen"); break;
			case 6: printf("sixteen"); break;
			case 7: printf("seventeen"); break;
			case 8: printf("eighteen"); break;
			case 9: printf("nineteen"); break;
		}
	}
	printf("\n");

	return 0;
}
