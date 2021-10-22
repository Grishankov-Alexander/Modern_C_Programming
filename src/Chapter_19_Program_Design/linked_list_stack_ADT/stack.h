/*
 * Abstract Generic Stack module
*/


typedef struct stack *StackPtr;


/* Create new stack on the heap.
 * 
 * Returns pointer to new stack.
 * Returns Null on allocation failure
*/
StackPtr stackCreate(void);


/* Removes stack s from the heap
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackDestroy(StackPtr s);


/* Removes all contents of the stack s
 * 
 * Can create memroy leaks if underlying
 * item was allocated on the heap.
 * User should be resbonsible for
 * for deallocating any item by calling stackPop()
 * and calling free() on the result
*/
void stackClear(StackPtr s);


// Adds item to the stack
void stackPush(StackPtr s, void *item);


/* Retrieves last stack item.
 *
 * Unsafe: Stack can be empty.
 * User should call stackIsEmpty() prior to calling
 * this function.
 *
 * Returns popped item.
*/
void *stackPop(StackPtr s);


/* Returns 1 is stack is empty,
 * Returns 0 otherwise.
*/
int stackIsEmpty(StackPtr s);


// Returns 0 always
int stackIsFull(StackPtr s);
