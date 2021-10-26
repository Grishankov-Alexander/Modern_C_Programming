/*
 * Fucking crazy queue implementation.
 *
 * Queue of specified size will be created.
 * When inserting an item into the full queue,
 * you'll lose the oldest item.
 *
 * The idea behind this implementation was to
 * challenge myself and to have fun.
*/


#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "queue.h"


typedef struct Queue {
	void **items;	// void * array on the heap
	void **first;	// pointer to first item
	void **last;	// pointer to last item
	size_t size;	// maximum queue size
} Queue;


/*
 * Create new heap with specified size on the heap.
 *
 * Return pointer to the queue.
 * Return NULL on failure.
*/
Queue *queueCreate(size_t size)
{
	Queue *q = malloc(sizeof *q);
	if (!q)
		return NULL;

	q->items = malloc(sizeof *q->items * size);
	if (!q->items) {
		free(q);
		return NULL;
	}

	q->first = q->last = NULL;
	q->size = size;

	return q;
}


/*
 * Free the memory allocated for the queue.
 *
 * Warining:	Dangerous when underlying items
 *		are allocated on the heap.
*/
void queueDestroy(Queue *q)
{
	free(q->items);
	free(q);
}


/*
 * Make queue *q empty
 *
 * Warining:	Dangerous when underlying items
 *		are allocated on the heap.
 * 
 * Return pointer to the queue
*/
Queue *queueClear(Queue *q)
{
	q->first = q->last = NULL;

	return q;
}


/*
 * Create new queue with size new_size.
 * Copy items from q into the new queue.
 * Destroy q.
 *
 * Return NULL on failure to create new queue.
*/
Queue *queueResize(Queue *q, size_t new_size)
{
	Queue *newq;

	newq = queueCreate(new_size);
	if (!newq)
		return NULL;

	queueCopy(newq, q);
	queueDestroy(q);

	return newq;
}


/*
 * Clear q1 and copy items from oldest to newest from q2 into q1.
 *
 * Return q1 on success.
 * Return q1 unchanged if q2 is empty queue
*/
Queue *queueCopy(Queue * restrict q1, const Queue * restrict q2)
{
	void **item_ptr;
	size_t max_sz;

	max_sz = q1->size;
	item_ptr = q2->first;

	if (!item_ptr)
		return q1;

	queueClear(q1);

	while (max_sz) {
		queueInsert(q1, *item_ptr);
		if (item_ptr == q2->last)
			break;
		item_ptr = q2->items + (item_ptr + 1 - q2->items) % q2->size;
		max_sz--;
	}

	return q1;
}


/*
 * Return number of items in the queue.
*/
size_t queueSize(Queue *q)
{
	ptrdiff_t ptr_diff;

	if (!q->first)
		return 0;

	ptr_diff = q->last - q->first;

	if (ptr_diff < 0)
		return q->size + ptr_diff + 1;
	return ptr_diff + 1;
}


/*
 * Return true if q is full.
*/
bool queueIsFull(Queue *q)
{
	return queueSize(q) == q->size;
}


/*
 * Return true if q is empty.
*/
bool queueIsEmpty(Queue *q)
{
	return queueSize(q) == 0;
}


/*
 * Insert new item in the queue.
 *
 * NOTICE!	if the queue is full
 * 		it will rewrite the oldest itme
 *
 * Return inserted item
*/
void *queueInsert(Queue *q, void *item)
{
	// first is NULL, last is NULL
	if (!q->last)
		return *(q->first = q->last = q->items) = item;

	// Handles boundary when advancing last
	q->last = q->items + (q->last + 1 - q->items) % q->size;
	// First need to be advanced when the queue is full
	if (q->last == q->first)
		// Handles boundary when advancing first
		q->first = q->items + (q->first + 1 - q->items) % q->size;

	return *q->last = item;
}


/*
 * Return the oldest queue item and advance the queue.
 * Return NULL if queue is empty
*/
void *queueGet(Queue *q)
{
	void *item;

	if (!q->first)
		return NULL;

	item = *q->first;

	// Make queue empty if it was last element. Advance queue otherwise.
	if (q->first == q->last)
		q->first = q->last = NULL;
	else
		// Handles boundary when advancing first
		q->first = q->items + (q->first + 1 - q->items) % q->size;

	return item;
}


/*
 * Return the oldest queue item without advancing the queue
 * Return NULL if queue is empty
*/
void *queuePeek(Queue *q)
{
	return q->first ? *q->first : NULL;
}
