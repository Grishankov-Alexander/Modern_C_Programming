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

	// Function that will be used to free the memory
	// of the underlying data for each Node in the List.
	void (*cleanFunc) (NodeDataType);

	// Create node with specified data and add it to the end of the list.
	// If SLList *self is NULL - return NULL
	// If SLList *self is empty list - Creates first node of the list.
	// Returns pointer to new node.
	// Returns NULL on FAILURE.
	Node * (*addNode) (SLList *self, NodeDataType data);

	// Create new Node with specified data. Insert it after Node *after.
	// If Node *after is NULL - return NULL
	// If SLList *self is NULL - return NULL
	Node *(*insertAfter) (SLList *self, NodeDataType data, Node *after);

	Node *(*insertBefore) (SLList *self, NodeDataType data, Node *before);

	void (*clearList) (SLList *self);

	void (*removeNode) (SLList *self, Node *n);
};


/*
 * Public functions on list
*/

// Create and init new list.
// void (*cleanFunc) (NODE_DATA_TYPE)
// cleanFunc - pointer to the function that will be used to
//	free the memory for each data in the Node.
//	Should be specified if Nodes will have
//	custom type defined with macro NODE_DATA_TYPE
//	prior to including "sllist.h" header.
//	Otherwise should be NULL
SLList newList(void (*cleanFunc) (NodeDataType));


#endif /* #ifndef SLLLIST_H */
