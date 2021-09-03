/*
 * Simple stack implementation.
 * Uses global variables and functions
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define STACK_SIZE 10


char stack[STACK_SIZE], *top_ptr;


void push(char c);
char pop(void);
void clear(void);
bool is_empty(void);
bool is_full(void);

void stack_underflow(void);
void stack_overflow(void);


int main(void)
{
	char c;
	bool unmatched = false;

	clear();

	printf("Enter parentheses or braces: ");

	while ((c = getchar()) != '\n') {
		switch (c) {
			case '(': case '[': case '{':
				push(c); break;
			case ')':
				if (pop() != '(')
					unmatched = true;
				break;
			case ']':
				if (pop() != '[')
					unmatched = true;
				break;
			case '}':
				if (pop() != '{')
					unmatched = true;
				break;
		}
	}

	if (unmatched)
		printf("Unmatched braces/parantheses.\n");
	else if (is_empty())
		printf("Nested properly.\n");
	else
		printf("Closing braces/parenthesis missing.\n");

	return 0;
}


void push(char c)
{
	if (is_full())
		stack_overflow();
	*top_ptr++ = c;
}


char pop(void)
{
	if (is_empty())
		stack_underflow();
	return *--top_ptr;
}


void clear(void)
{
	top_ptr = stack;
}


bool is_empty(void)
{
	return top_ptr == stack;
}


bool is_full(void)
{
	return top_ptr == stack + STACK_SIZE;
}


void stack_underflow(void)
{
	printf("Stack underflow; Exit 1\n");
	exit(EXIT_FAILURE);
}


void stack_overflow(void)
{
	printf("Stack overflow; Exit 1\n");
	exit(EXIT_FAILURE);
}
