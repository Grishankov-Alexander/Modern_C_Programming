/*
 * RPN calculator
 *
 * Calculates expressions in Reverse Polish Notation:
 * 9 7 4 - /
 * Translates into: 9 / (7 - 4)
*/


#include <stdio.h>
#include <ctype.h>
#include "stack.h"


int main(void)
{
	double d, lo, ro;
	char c;

	printf("Enter RPN expression: ");
	while ((c = getchar())) {
		if (isspace(c))
			continue;
		else if (c != '+' && c != '-' && c != '*' && c != '/' && c != '=') {
			ungetc(c, stdin);
			if (scanf("%lf", &d))
				push(d);
			continue;
		}
		switch (c) {
			case '+': ro = pop(); lo = pop(); push(lo + ro); break;
			case '-': ro = pop(); lo = pop(); push(lo - ro); break;
			case '*': ro = pop(); lo = pop(); push(lo * ro); break;
			case '/': ro = pop(); lo = pop(); push(lo / ro); break;
			case '=': printf("Result: %lg\n", pop()); break; 
			default: break;
		}
	}

	return 0;
}
