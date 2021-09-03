/*
 * Adds two fractions
*/

#include <stdio.h>

int main(void)
{
	int num1, denom1, num2, denom2;
	char o;
	double n1, n2, result;

	printf("Enter two fractions separated by operation (+-/*): ");
	(void)scanf("%d / %d %c %d / %d", &num1, &denom1, &o, &num2, &denom2);

	n1 = (double)num1 / denom1;
	n2 = (double)num2 / denom2;

	switch (o) {
		case '+':
			result = n1 + n2;
			break;
		case '-':
			result = n1 - n2;
			break;
		case '*':
			result = n1 * n2;
			break;
		case '/':
			result = n1 / n2;
			break;
		default:
			printf("Illegal operator: %c\n", o);
			return 1;
	}

	printf("%d/%d %c %d/%d = %g\n", num1, denom1, o, num2, denom2, result);

	return 0;
}

