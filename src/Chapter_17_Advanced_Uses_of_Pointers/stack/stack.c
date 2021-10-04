/*
 * Generic stack implementation
 * using a singly-linked list idiom.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct stack {
	void *data;
	struct stack *next;
};


// Allocates new stack item.
// Updates top pointer of the stack.
// Return false if data is NULL.
// Return false if allocation fails
bool push(struct stack **topptr, void *data);

// Free memory allocated for the top stack item.
// Updates top pointer of the stack
// Returns pointer to the data of top item.
// Returns NULL if stack is empty
void *pop(struct stack **topptr);

// Free memory of all stack items.
// Free memory for each data of stack item using freeDataFunc.
void clearStack(struct stack **topptr, void (*freeDataFunc) (void *));


// Function that frees the underlying string data of the stack.
// Assuming that void *data of the stack is char **
void freeString(void *str);


int main(void)
{
	struct stack *top = NULL;
	char *s1 = malloc(sizeof "Hello"), *s2 = malloc(sizeof "World"), *s3;
	strcpy(s1, "Hello"), strcpy(s2, "World");

	push(&top, &s1);
	push(&top, &s2);
	s3 = *(char **) pop(&top);
	printf("s3 = %s\n", s3);

	free(s3);
	clearStack(&top, freeString);

	return 0;
}


bool push(struct stack **topptr, void *data)
{
	if (!data)
		return false;

	struct stack *new = malloc(sizeof *new);
	if (!new)
		return false;

	new->next = *topptr;
	new->data = data;
	*topptr = new;
	
	return true;
}


void *pop(struct stack **topptr)
{
	struct stack *top;
	void *data;
	
	if (!*topptr)
		return NULL;

	top = *topptr;
	data = top->data;
	*topptr = top->next;

	free(top);

	return data;
}


void clearStack(struct stack **topptr, void (*freeDataFunc) (void *))
{
	struct stack *top;

	while (*topptr) {
		top = *topptr;
		*topptr = top->next;
		if (freeDataFunc)
			freeDataFunc(top->data);
		free(top);
	}
}


void freeString(void *str)
{
	free(*(char **) str);
}
