/*
 * Demonstrates how Abstract Generic Stack Data Type can be used
*/


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "stack.h"


#define INITIAL_STACK_SIZE 4
#define STACK_SIZE_ADDEND 2

#define PRINT_STACK_INFO_FOR_TYPE(StackPtr, Type)							\
{													\
	printf("Stack info {");										\
	printf(" Size: %zu;", stackSize(StackPtr));							\
	printf(" Is Full: %s;", stackIsFull(StackPtr) ? "true" : "false");				\
	printf(" Is Empty: %s;", stackIsEmpty(StackPtr) ? "true" : "false");				\
	printf(" Last Element: %g;", stackIsEmpty(StackPtr) ? NAN : STACK_PEEK_TYPE(StackPtr, Type));	\
	printf(" }\n");											\
}

#define STACK_PEEK_TYPE(StackPtr, Type)		(*(Type *) stackPeek(StackPtr))

#define STACK_POP_TYPE(StackPtr, Type)		(*(Type *) stackPop(StackPtr))


int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6};
	size_t n;
	Stack *s;

	// Stack creation
	s = stackCreate(INITIAL_STACK_SIZE, STACK_SIZE_ADDEND);
	if (!s)
		printf("Couldn't allocate memory for the stack\n");

	for (n = 0; n < sizeof a / sizeof *a; n++) {
		if (!stackPush(s, a + n))
			printf("Failure: Stack can't allocate more memory\n");
		PRINT_STACK_INFO_FOR_TYPE(s, int);
	}
	printf("\n");

	while (stackPop(s))
		PRINT_STACK_INFO_FOR_TYPE(s, int);

	stackClear(s);
	stackDestroy(s);

	return 0;
}
