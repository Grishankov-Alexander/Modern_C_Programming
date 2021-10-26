/*
 * Crazy queue Abstract Data Type module
 * Uses dynamically allocated array.
 *
 * Queue of specified size will be created.
 * When inserting an item into the full queue,
 * you'll lose the oldest item.
 *
 * The idea behind this implementation was to
 * challenge myself and to have fun.
*/


#ifndef CRAZY_QUEUE_H
#define CRAZY_QUEUE_H


#include <stddef.h>
#include <stdbool.h>


typedef struct Queue Queue;


/*
 * Create new heap with specified size on the heap.
 *
 * Return pointer to the queue.
 * Return NULL on failure.
*/
Queue *queueCreate(size_t size);


/*
 * Free the memory allocated for the queue.
 *
 * Warining:	Dangerous when underlying items
 *		are allocated on the heap.
*/
void queueDestroy(Queue *q);


/*
 * Make queue *q empty
 *
 * Warining:	Dangerous when underlying items
 *		are allocated on the heap.
 * 
 * Return pointer to the queue
*/
Queue *queueClear(Queue *q);


/*
 * Create new queue with size new_size.
 * Copy items from q into the new queue.
 * Destroy q.
 *
 * Return NULL on failure to create new queue.
*/
Queue *queueResize(Queue *q, size_t new_size);


/*
 * Clear q1 and copy items from oldest to newest from q2 into q1.
 *
 * Return q1 on success.
 * Return q1 unchanged if q2 is empty queue
*/
Queue *queueCopy(Queue * restrict q1, const Queue * restrict q2);


/*
 * Return number of items in the queue.
*/
size_t queueSize(Queue *q);


/*
 * Return true if q is full.
*/
bool queueIsFull(Queue *q);


/*
 * Return true if q is empty.
*/
bool queueIsEmpty(Queue *q);


/*
 * Insert new item in the queue.
 *
 * NOTICE!	if the queue is full
 * 		it will rewrite the oldest itme
 *
 * Return inserted item
*/
void *queueInsert(Queue *q, void *item);


/*
 * Return the oldest queue item and advance the queue.
 * Return NULL if queue is empty
*/
void *queueGet(Queue *q);


/*
 * Return the oldest queue item without advancing the queue
 * Return NULL if queue is empty
*/
void *queuePeek(Queue *q);


#endif	/* #ifndef CRAZY_QUEUE_H */
