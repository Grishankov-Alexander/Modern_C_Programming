/*
 * Generic Stack Abstract Data Type module
 * implemented using dynamic array
*/


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"


typedef struct Stack {
	void **items;
	size_t size;
	size_t max_size;
	size_t size_addend;
} Stack;


/*
 * Create new stack with size initial_size on the heap.
 *
 * initial_size:	how much items of type void * will be allocated
 * 			when stack is created.
 * size_addend:		Shows how much space will be added to stack if it
 * 			reaches its intitial_size.
 *
 * Return address of created stack.
 * Return NULL on failure.
*/
Stack *stackCreate(size_t initial_size, size_t size_addend)
{
	Stack *s = malloc(sizeof *s);
	if (!s)
		return NULL;

	s->items = malloc(sizeof *(s->items) * initial_size);
	if (!s->items) {
		free(s);
		return NULL;
	}

	s->size = 0;
	s->max_size = initial_size;
	s->size_addend = size_addend;

	return s;
}


/*
 * Free space allocated for stack items and the stack itself.
*/
void stackDestroy(Stack *s)
{
	free(s->items);
	free(s);
}


/*
 * Clear stack of all items.
*/
void stackClear(Stack *s)
{
	s->size = 0;
}


/*
 * Adds new item of type void * to the stack.
 *
 * Return item on sucess.
 * Return Null on failure.
*/
void *stackPush(Stack *s, void *item)
{
	void **new_items;

	if (s->size == s->max_size) {
		new_items = realloc(
			s->items,
			sizeof *(s->items) * (s->max_size + s->size_addend)
		);
		// Reallocation fails
		if (!new_items)
			return NULL;
		s->items = new_items;
		s->max_size += s->size_addend;
	}

	return s->items[s->size++] = item;
}


/*
 * Pop and return last stack item
 *
 * Return NULL if stack is empty
*/
void *stackPop(Stack *s)
{
	if (!s->size)
		return NULL;
	return s->items[--s->size];
}


/*
 * Return last item of the stack without popping
 *
 * Return NULL if stack is empty
*/
void *stackPeek(Stack *s)
{
	if (!s->size)
		return NULL;
	return s->items[s->size - 1];
}


/*
 * Return number of items in the stack
*/
size_t stackSize(Stack *s)
{
	return s->size;
}


/*
 * Return true if stack is empty
 *
 * Return false if stack is not empty
*/
bool stackIsEmpty(Stack *s)
{
	return s->size ? false : true;
}


/*
 * Return true if stack is full
 *
 * Return false if stack is not full
*/
bool stackIsFull(Stack *s)
{
	return s->size == s->max_size ? true : false;
}
