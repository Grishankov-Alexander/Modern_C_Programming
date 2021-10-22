/*
 * Generic Stack Abstract Data Type module
*/


#ifndef STACK_ADT
#define STACK_ADT


struct Stack;
typedef struct Stack Stack;


/* Create new stack on the heap.
 * 
 * Returns pointer to the new stack.
*/
Stack *stackCreate(void);


/* Removes stack s from the heap
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackDestroy(Stack *s);


/* Removes all contents of the stack s
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackClear(Stack *s);


// Adds item to the stack
void stackPush(Stack *s, void *item);


/* Retrieves last stack item.
 *
 * Unsafe: Stack can be empty.
 * User should call stackIsEmpty() prior to calling
 * this function.
 *
 * Returns popped item.
*/
void *stackPop(Stack *s);


// Returns last item from the stack without changing the stack
void *stackPeek(Stack *s);


/* Returns 1 is stack is empty,
 * Returns 0 otherwise.
*/
int stackIsEmpty(Stack *s);


// Returns 0 always
int stackIsFull(Stack *s);


#endif /* #ifndef STACK_ADT */
