/*
 * Program that evaluates the expression.
 *
 * Precedence does not exist.
 * Evaluates from left to right.
*/


#include <stdio.h>


int main(void) {
	float f, res;
	char ch;

	printf("Enter an expression: ");

	for (scanf("%f%c", &res, &ch); ch != '\n'; scanf("%c", &ch)) {
		switch (ch) {
			case ' ':
				continue;
			case '+':
				scanf("%f", &f);
				res += f;
				break;
			case '-':
				scanf("%f", &f);
				res -= f;
				break;
			case '*':
				scanf("%f", &f);
				res *= f;
				break;
			case '/':
				scanf("%f", &f);
				res /= f;
				break;
		}
	}

	printf("Result of an expression: %g\n", res);

	return 0;
}
