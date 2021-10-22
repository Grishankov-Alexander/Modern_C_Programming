/*
 * Generic Stack Abstract Data Type module implementation
 * using a singly linked list.
*/


#include <stdlib.h>
#include "stack.h"


typedef struct StackNode {
	void *item;
	struct StackNode *prev;
} StackNode;


typedef struct Stack {
	StackNode *head;
} Stack;


/* Create new stack on the heap.
 * 
 * Returns pointer to the new stack.
*/
Stack *stackCreate(void)
{
	Stack *s;

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
void stackDestroy(Stack *s)
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
void stackClear(Stack *s)
{
	StackNode *popped;

	while (s->head) {
		popped = s->head;
		s->head = s->head->prev;
		free(popped);
	}
}


// Adds item to the stack
void stackPush(Stack *s, void *item)
{
	StackNode *pushed;

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
void *stackPop(Stack *s)
{
	StackNode *popped;
	void *item;

	popped = s->head;
	item = s->head->item;
	s->head = s->head->prev;
	free(popped);

	return item;
}


// Returns last item from the stack without changing the stack
void *stackPeek(Stack *s)
{
	return s->head->item;
}


/* Returns 1 is stack is empty,
 * Returns 0 otherwise.
*/
int stackIsEmpty(Stack *s)
{
	return s->head == NULL ? 1 : 0;
}


// Returns 0 always
int stackIsFull(Stack *s)
{
	return (void *) s && NULL;
}
