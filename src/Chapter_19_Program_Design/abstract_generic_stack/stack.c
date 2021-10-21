/*
 * Abstract Generic Stack module implementation
*/


#include <stdlib.h>
#include "stack.h"


struct stack_node {
	void *item;
	struct stack_node *prev;
};


struct stack {
	struct stack_node *head;
};


/* Create new stack on the heap.
 * 
 * Returns pointer to the new stack.
 * Returns Null on allocation failure
*/
StackPtr stackCreate(void)
{
	StackPtr s;

	s = malloc(sizeof *s);
	s->head = NULL;

	return s;
}


/* Removes stack s from the heap
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackDestroy(StackPtr s)
{
	stackClear(s);
	free(s);
}


/* Removes all contents of the stack s
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackClear(StackPtr s)
{
	struct stack_node *popped;

	while (s->head) {
		popped = s->head;
		s->head = s->head->prev;
		free(popped);
	}
}


// Adds item to the stack
void stackPush(StackPtr s, void *item)
{
	struct stack_node *pushed;

	pushed = malloc(sizeof *pushed);
	pushed->item = item;
	pushed->prev = s->head;
	s->head = pushed;
}


/* Retrieves last stack item.
 *
 * Unsafe: Stack can be empty.
 * User should call stackIsEmpty() prior to calling
 * this function.
 *
 * Returns popped item.
*/
void *stackPop(StackPtr s)
{
	struct stack_node *popped;
	void *item;

	popped = s->head;
	item = s->head->item;
	s->head = s->head->prev;
	free(popped);

	return item;
}


/* Returns 1 is stack is empty,
 * Returns 0 otherwise.
*/
int stackIsEmpty(StackPtr s)
{
	return s->head == NULL ? 1 : 0;
}


// Returns 0 always
int stackIsFull(StackPtr s)
{
	return 0 & *(int *) s;
}
