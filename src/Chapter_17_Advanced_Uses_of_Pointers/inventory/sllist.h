/*
 * Singly linked list declarations
*/


#ifndef SLLLIST_H
#define SLLIST_H


#include "node.h"


typedef struct sllist SLList;


struct sllist {
	Node *head;
	Node *tail;

	/*
	 * List member functions
	*/

	// Create node with specified data and add it to the end of the list.
	// If SLList *self is NULL - return NULL
	// If SLList *self is empty list - Creates first node of the list.
	// Returns pointer to new node.
	// Returns NULL on FAILURE.
	Node * (*addNode) (SLList *self, NodeDataType data);

	// Create new Node with specified data. Insert it after Node *after.
	// If Node *after is NULL - return NULL
	// If SLList *self is NULL - return NULL
	// Update tail if Node *after is the current tail of the list.
	Node * (*insertAfter) (SLList *self, NodeDataType data, Node *after);

	// Create new Node with specified data. Insert it before Node *before.
	// If Node *before is NULL - return NULL
	// If SLList *self is NULL - return NULL
	// Update head if Node *head is the current head of the list.
	Node * (*insertBefore) (SLList *self, NodeDataType data, Node *before);

	// Returns pointer to Node that contains specified data.
	// Comparison is done using macro function from node.h
	Node * (*findNode) (SLList *self, NodeDataType data);

	// Remove all nodes from the list *self
	// If self is NULL - do nothing
	void (*clearList) (SLList *self);

	// Remove specified node *n from the list *self
	// if n is NULL - do nothing
	// if self is NULL - do nothing
	void (*removeNode) (SLList *self, Node *n);
};


/*
 * Public functions on list
*/

// Create and init new list.
SLList newList(void);


#endif /* #ifndef SLLLIST_H */
