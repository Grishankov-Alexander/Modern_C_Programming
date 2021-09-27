/*
 * Singly linked list implementation
*/


#include <stdio.h>
#include <stdlib.h>

#include "sllist.h"


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
static Node *m_insertAfter (SLList *self, NodeDataType data, Node *after)
{
	if (!self || !after)
		return NULL;
	else {
		return insertAfter(data, after);
	}
}


static void m_clearList(SLList *self)
{
	Node *p = self->head;

	while (p != NULL)
	{
		self->cleanFunc(p->data);
		p = removeNode(p);
	}

	self->head = NULL;
	self->tail = NULL;
}



/*
 * Public functions of the list
*/

// Create and init new list
SLList newList(void (*cleanFunc) (NodeDataType))
{
	SLList new;

	new.head = NULL;
	new.tail = NULL;
	new.cleanFunc = cleanFunc;
	new.addNode = &m_addNode;
	new.insertAfter = &m_insertAfter;
	new.clearList = &m_clearList;

	return new;
}
