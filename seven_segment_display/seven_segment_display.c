

#include <stdio.h>
#include <stdbool.h>


int main(void)
{
	const int segments[][7] = {
		[0][0] = 1, 1, 1, 1, 1, 1,
		[1][1] = 1, 1,
		[2][0] = 1, 1, 0, 1, 1, 0, 1,
		[3][0] = 1, 1, 1, 1, [3][6] = 1,
		[4][1] = 1, 1, [4][5] = 1, 1,
		[5][0] = 1, 0, 1, 1, 0, 1, 1,
		[6][0] = 1, 0, 1, 1, 1, 1, 1,
		[7][0] = 1, 1, 1,
		[8][0] = 1, 1, 1, 1, 1, 1, 1,
		[9][0] = 1, 1, 1, 1, 0, 1, 1
	};

	for (int i = 0; i < 10; ++i) {
		printf("%s\n", segments[i][0] ? " _" : "");
		printf("%c", segments[i][5] ? '|' : ' ');
		printf("%c", segments[i][6] ? '_' : ' ');
		printf("%s\n", segments[i][1] ? "|" : "");
		printf("%c", segments[i][4] ? '|' : ' ');
		printf("%c", segments[i][3] ? '_' : ' ');
		printf("%s\n\n", segments[i][2] ? "|" : "");
	}

	return 0;
}
