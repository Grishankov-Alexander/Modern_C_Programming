/*
 * Stack definitions
*/


#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


double stack[STACK_SZ];
double *head = stack;


double pop(void)
{
	if (is_empty())
		stack_underflow();
	return *--head;
}


void push(double d)
{
	if (is_full())
		stack_overflow();
	*head++ = d;
}


Bool is_empty(void)
{
	return head == stack;
}


Bool is_full(void)
{
	return (head - stack) == STACK_SZ;
}


void make_empty(void)
{
	head = stack;
}


void stack_overflow(void)
{
	printf("Stack overflow\n");
	exit(EXIT_FAILURE);
}


void stack_underflow(void)
{
	printf("Stack underflow\n");
	exit(EXIT_FAILURE);
}
