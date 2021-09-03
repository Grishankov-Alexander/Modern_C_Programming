/*
 * Program evaluates expressions using Reverse Polish Notation.
 *
 * For example: "5 8 * 4 9 - / = "expression will evaluate to -8.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define STACK_SIZE 10


typedef char number;


static number stack[STACK_SIZE];
static int stack_pos;


// Operate on global stack
static void push(number n);
static number pop(void);
static void clear(void);
static bool is_empty(void);
static bool is_full(void);

// Print message and terminate the program with EXIT_FAILURE
static void stack_underflow(void);
static void stack_overflow(void);


int main(void)
{
	// left operand, right operand
	char lo, ro;
	char ch;

	printf("Enter an RPN expression: ");
	
	for ( ; ; ) {

		scanf(" %c", &ch);

		if ('0' <= ch && ch <= '9') {
			push(ch - '0');
			continue;
		} else if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
			ro = pop(), lo = pop();

		switch (ch) {
			case '+':
				push(lo + ro);
				break;
			case '-':
				push(lo - ro);
				break;
			case '*':
				push(lo * ro);
				break;
			case '/':
				push(lo / ro);
				break;
			case '=':
				printf("Value of expression: %d\n", (int) pop());
				clear();
				while ((ch = getchar() != '\n'))
					;
				printf("Enter an RPN expression: ");
				break;
			default:
				return 0;
		}
	}
}


static void push(number n)
{
	if (is_full())
		stack_overflow();
	stack[stack_pos++] = n;
}


static number pop(void)
{
	if (is_empty())
		stack_underflow();
	return stack[--stack_pos];
}


static void clear(void)
{
	stack_pos = 0;
}


static bool is_empty(void)
{
	return stack_pos == 0;
}


static bool is_full(void)
{
	return stack_pos == STACK_SIZE;
}


static void stack_underflow(void)
{
	printf("stack underflow: not enough operands!\n");
	exit(EXIT_FAILURE);
}


static void stack_overflow(void)
{
	printf("Stack overflow: too much operands!\n");
	exit(EXIT_FAILURE);
}
