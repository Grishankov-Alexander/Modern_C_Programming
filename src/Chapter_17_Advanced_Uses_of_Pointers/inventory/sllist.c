/*
 * Singly linked list implementation
*/


#include <stdio.h>
#include <stdlib.h>

#include "sllist.h"


/*
 * Helper static functions
*/

// Find the Node that precedes Node *n.
// Return NULL if previous node not found.
// Return NULL if n is a head of the list.
// Return NULL if list is empty
static Node *findPrev(SLList *self, Node *n)
{
	Node **prev;

	if (!self->head || n == self->head)
		return NULL;

	// Assume that previous Node is right before *n in memory
	else if ((n - sizeof *n)->next == n)
		return n - sizeof *n;

	for (
		prev = &self->head;
		(*prev)->next && (*prev)->next != n;
		prev = &(*prev)->next
	) ;

	return *prev;
}


/*
 * Member functions of the list
*/

// Create node with specified data and add it to the end of the list.
// If SLList *self is NULL - return NULL
// If SLList *self is empty list - Creates first node of the list.
// Returns pointer to new node.
// Returns NULL on FAILURE.
static Node *m_addNode(SLList *self, NodeDataType data)
{
	if (!self)
		return NULL;
	else if (!self->head)
		self->tail = self->head = newNode(data);
	else
		self->tail = insertAfter(data, self->tail);

	return self->tail;
}


// Create new Node with specified data. Insert it after Node *after.
// If Node *after is NULL - return NULL
// If SLList *self is NULL - return NULL
// Update tail if Node *after is the current tail of the list.
static Node *m_insertAfter (SLList *self, NodeDataType data, Node *after)
{
	Node *new_node;

	if (!self || !after)
		return NULL;

	new_node = insertAfter(data, after);
	if (!new_node)
		return NULL;
	else if (after == self->tail)
		self->tail = new_node;

	return new_node;
}

// Create new Node with specified data. Insert it before Node *before.
// If Node *before is NULL - return NULL
// If SLList *self is NULL - return NULL
// Update head if Node *head is the current head of the list.
static Node *m_insertBefore (SLList *self, NodeDataType data, Node *before)
{
	Node *new_node, *prev;

	if (!self || !before)
		return NULL;

	new_node = newNode(data);
	if (!new_node)
		return NULL;

	new_node->next = before;

	if (before == self->head)
		self->head = new_node;
	else {
		prev = findPrev(self, before);
		prev->next = new_node;
	}

	return new_node;
}


// Remove all nodes from the list *self
// If self is NULL - do nothing
static void m_clearList(SLList *self)
{
	Node *p;

	if (!self)
		return;

	p = self->head;

	while (p != NULL)
		p = removeNode(p);

	self->head = NULL;
	self->tail = NULL;
}


// Remove specified node *n from the list *self
// if n is NULL - do nothing
// if self is NULL - do nothing
void m_removeNode (SLList *self, Node *n)
{
	Node *prev, *next;

	if (!self || !n)
		return;

	prev = findPrev(self, n);
	next = removeNode(n);

	if (!next)
		self->tail = prev;
	if (!prev)
		self->head = next;
	else
		prev->next = next;
}


// Returns pointer to Node that contains specified data.
// Comparison is done using macro function from node.h
static Node *m_findNode(SLList *self, NodeDataType data)
{
	Node *p;

	for (p = self->head; p; p = p->next)
		if (compareData(p->data, data) == 0)
			break;

	return p;
}


// Returns pointer to Node whose data is bigger than data argument
// Returns NULL if not found
static Node *m_findBigger(SLList *self, NodeDataType data)
{
	Node *p;

	for (p = self->head; p; p = p->next)
		if (compareData(p->data, data) > 0)
			break;

	return p;
}



/*
 * Public functions of the list
*/

// Create and init new list
SLList newList(void)
{
	SLList new;

	new.head = NULL;
	new.tail = NULL;
	new.addNode = &m_addNode;
	new.insertAfter = &m_insertAfter;
	new.insertBefore = &m_insertBefore;
	new.removeNode = &m_removeNode;
	new.clearList = &m_clearList;
	new.findNode = &m_findNode;
	new.findBigger = &m_findBigger;

	return new;
}
