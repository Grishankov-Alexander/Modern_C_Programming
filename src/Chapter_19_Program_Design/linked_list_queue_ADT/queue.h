/*
 * Queue Abstract Data Type Module
*/


#ifndef LINKED_LIST_QUEUE_ADT
#define LINKED_LIST_QUEUE_ADT


#include <stddef.h>
#include <stdbool.h>


typedef struct Queue Queue;


/*
 * Create empty queue on the heap.
 *
 * Return pointer to queue.
 * Return NULL on failure.
*/
Queue *queueCreate(void);


/*
 * Deallocates memory for the queue.
 *
 * NOTE:	Underlying data will be lost.
 * 		Can create dangling pointers.
*/
void queueDestroy(Queue *q);


/*
 * Clears the queue.
 *
 * NOTE:	Underlying data will be lost.
 * 		Can create dangling pointers.
*/
Queue *queueClear(Queue *q);


/*
 * Append contents of q2 on top of q1.
 *
 * Return q1
 * Return NULL on failure.
*/
Queue *queueCopy(Queue * restrict q1, const Queue * restrict q2);


/*
 * Return number of items in the queue
*/
size_t queueSize(Queue *q);


/*
 * Return true if queue is full.
*/
bool queueIsFull(Queue *q);


/*
 * Return true if queue is empty.
*/
bool queueIsEmpty(Queue *q);


/*
 * Insert new item into the queue.
 *
 * Return inserted item (void *).
 * Return NULL on insertion failure.
*/
void *queueInsert(Queue *q, void *item);


/*
 * Pop the oldest item from the queue.
 *
 * Return NULL if queue is empty.
*/
void *queueGet(Queue *q);

/*
 * Return the oldest queue item
 * Return NULL if queue is empty
*/
void *queuePeek(Queue *q);


#endif /* #ifndef LINKED_LIST_QUEUE_ADT */
