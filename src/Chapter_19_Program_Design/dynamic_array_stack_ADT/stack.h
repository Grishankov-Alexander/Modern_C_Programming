/*
 * Generic Stack Abstract Data Type module
*/


#ifndef STACK_ADT
#define STACK_ADT


#include <stddef.h>
#include <stdbool.h>


typedef struct Stack Stack;


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
Stack *stackCreate(size_t initial_size, size_t size_addend);


/*
 * Free space allocated for stack items and the stack itself.
*/
void stackDestroy(Stack *s);


/*
 * Clear stack of all items.
*/
void stackClear(Stack *s);


/*
 * Adds new item of type void * to the stack.
 *
 * Return item on sucess.
 * Return Null on failure.
*/
void *stackPush(Stack *s, void *item);


/*
 * Pop and return last stack item
 *
 * Return NULL if stack is empty
*/
void *stackPop(Stack *s);


/*
 * Return last item of the stack without popping
 *
 * Return NULL if stack is empty
*/
void *stackPeek(Stack *s);


/*
 * Return number of items in the stack
*/
size_t stackSize(Stack *s);


/*
 * Return true if stack is empty
 *
 * Return false if stack is not empty
*/
bool stackIsEmpty(Stack *s);


/*
 * Return true if stack is full
 *
 * Return false if stack is not full
*/
bool stackIsFull(Stack *s);


#endif /* #ifndef STACK_ADT */
