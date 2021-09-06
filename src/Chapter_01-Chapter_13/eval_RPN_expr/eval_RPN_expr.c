/*
 * Program evaluates expressions using Reverse Polish Notation.
 *
 * For example: "5 8 * 4 9 - / = "expression will evaluate to -8.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define STACK_SIZE 10
#define EXPR_STRING_SIZE 30


typedef int number;


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

// Programming project 15 from chapter 13 requires this
int eval_rpn_expr(const char* expr);
// Read at most n - 1 chars to s (exclude newline)
static int readln(char *s, int n);


int main(void)
{
	/* Worked all right but chapter 13 requires some change
	// left operand, right operand
	char lo, ro;
	char ch;

	printf("Enter an RPN expression: ");
	
	for ( ; ; ) {

		scanf(" %c", &ch);

		if ('0' <= ch && ch <= '9') {
			push(ch - '0');
			continue;
		}

		switch (ch) {
			case '+':
				ro = pop(), lo = pop();
				push(lo + ro);
				break;
			case '-':
				ro = pop(), lo = pop();
				push(lo - ro);
				break;
			case '*':
				ro = pop(), lo = pop();
				push(lo * ro);
				break;
			case '/':
				ro = pop(), lo = pop();
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
	*/

	char expr[EXPR_STRING_SIZE];

	printf("Enter RPN expression: ");
	readln(expr, sizeof expr);

	printf("Result: %d\n", eval_rpn_expr(expr));

	return 0;
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


int eval_rpn_expr(const char* expr)
{
	// Keep track on number of characters read by scanf
	int num_read;
	int n, lo, ro;

	// Clear stack
	clear();

	while (*expr) {
		if (sscanf(expr, "%d%n", &n, &num_read)) {
			push(n);
			expr += num_read;
			continue;
		}
		switch (*expr++) {
			case '+':	ro = pop(), lo = pop(), push(lo + ro); break;
			case '-':	ro = pop(), lo = pop(), push(lo - ro); break;
			case '*':	ro = pop(), lo = pop(), push(lo * ro); break;
			case '/':
					ro = pop(), lo = pop();
					if (!ro) {
						printf("Error: Division by zero\n");
						exit(EXIT_FAILURE);
					}
					push(lo / ro); break;
			case '=':	return pop();
			default:	break;
		}
	}

	return 0;
}


static int readln(char *s, int n)
{
	char c, *p;

	for (p = s; n > 1; n--, p++) {
		c = getchar();
		if (c == '\n')
			break;
		*p = c;
	}

	*p = 0;

	return p - s;
}
