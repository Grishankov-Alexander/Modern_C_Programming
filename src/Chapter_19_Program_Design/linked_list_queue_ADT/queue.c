/*
 * Queue Abstract Data Type Module Implementation
 * using a singly-linked list.
*/


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"


typedef struct QueueNode {
	void *item;
	struct QueueNode *next;
} QueueNode;


typedef struct Queue {
	struct QueueNode *first;
	struct QueueNode *last;
} Queue;


/*
 * Create empty queue on the heap.
 *
 * Return pointer to queue.
 * Return NULL on failure.
*/
Queue *queueCreate(void)
{
	Queue *new;

	new = malloc(sizeof *new);
	if (!new)
		return NULL;

	new->first = new->last = NULL;

	return new;
}


/*
 * Deallocates memory for the queue.
 *
 * NOTE:	Underlying data will be lost.
 * 		Can create dangling pointers.
*/
void queueDestroy(Queue *q)
{
	free(queueClear(q));
}


/*
 * Clears the queue.
 *
 * NOTE:	Underlying data will be lost.
 * 		Can create dangling pointers.
*/
Queue *queueClear(Queue *q)
{
	QueueNode *p_n;

	while (q->first) {
		p_n = q->first->next;
		free(q->first);
		q->first = p_n;
	}

	q->last = NULL;

	return q;
}


/*
 * Append contents of q2 on top of q1.
 *
 * Return q1
 * Return NULL on failure.
*/
Queue *queueCopy(Queue * restrict q1, const Queue * restrict q2)
{
	QueueNode *p_n;

	for (p_n = q2->first; p_n; p_n = p_n->next)
		if (!queueInsert(q1, p_n->item))
			return NULL;

	return q1;
}


/*
 *
*/
size_t queueSize(Queue *q)
{
	size_t sz_q;
	QueueNode *p_n;

	sz_q = 0;
	p_n = q->first;

	while (p_n) {
		sz_q++;
		p_n = p_n->next;
	}

	return sz_q;
}


/*
 * Return true if queue is full.
*/
bool queueIsFull(Queue *q)
{
	return !q;
}


/*
 * Return true if queue is empty.
*/
bool queueIsEmpty(Queue *q)
{
	return !q->first;
}


/*
 * Insert new item into the queue.
 *
 * Return inserted item (void *).
 * Return NULL on insertion failure.
*/
void *queueInsert(Queue *q, void *item)
{
	QueueNode *p_n;

	p_n = malloc(sizeof *p_n);
	if (!p_n)
		return NULL;

	p_n->item = item;
	p_n->next = NULL;

	if (!q->last)
		q->first = q->last = p_n;
	else {
		q->last->next = p_n;
		q->last = p_n;
	}

	return item;
}


/*
 * Pop the oldest item from the queue.
 *
 * Return NULL if queue is empty.
*/
void *queueGet(Queue *q)
{
	QueueNode *p_n;
	void *p_i;

	if (queueIsEmpty(q))
		return NULL;

	if (q->first == q->last)
		q->last = NULL;

	p_n = q->first;
	p_i = q->first->item;

	q->first = q->first->next;

	free(p_n);

	return p_i;
}

/*
 * Return the oldest queue item
 * Return NULL if queue is empty
*/
void *queuePeek(Queue *q)
{
	if (queueIsEmpty(q))
		return NULL;

	return q->first->item;
}
