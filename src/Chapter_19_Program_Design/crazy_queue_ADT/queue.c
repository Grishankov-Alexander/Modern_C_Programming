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


typedef struct queue {
	void **items;
	void **first;
	void **last;
	size_t size;
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
		return q->size - ptr_diff + 1;
	return ptr_diff + 1;
}


/*
 *
*/
bool queueResize(Queue *q, size_t new_size)
{
	size_t num_items;
	void **new_items;
	
	new_items = malloc(sizeof *new_items * new_size);
	if(!new_items)
	       return false;
	
	num_items = queueSize(q);

	// TODO
	free(q->items);
	q->items = new_items;
	q->first = new_items;
	q->last = 2;
	q->size = new_size;
}


/*
 * Free the memory allocated for the queue.
*/
void queueDestroy(Queue *q)
{
	free(q->items);
	free(q);
}


/*
 * Insert new item in the queue.
 *
 * NOTICE!	if the queue is full
 * 		it will rewrite the oldest itme
 *
 * Return inserted item on success.
 * Return NULL on failure.
*/
void *queueInsert(Queue *q, void *item)
{
	// first is NULL, last is NULL
	if (!q->last) {
		*(q->first = q->last = q->items) = item;
		return *q->last;
	}

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
*/
void *queueGet(Queue *q)
{
	void *item;

	if (!q->first)
		return NULL;

	item = q->first;

	// Make queue empty if it was last element. Advance queue otherwise.
	if (q->first == q->last)
		q->first = q->last = NULL;
	// Handles boundary when advancing first
	q->first = q->items + (q->first + 1 - q->items) % q->size;

	return item;
}


/*
 * Return the oldest queue item without advancing the queue
*/
void *queuePeek(Queue *q)
{
	return q->first ? *q->first : NULL;
}
