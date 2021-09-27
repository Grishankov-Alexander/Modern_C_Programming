/*
 * Node implementation
*/


#include <stdlib.h>

#include "node.h"


/*
 * Public functions on node
*/

// Creates new node on the heap.
// Return NULL on failure
// Return pointer no new Node on success.
Node *newNode(NodeDataType data)
{
	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->data = data;

	return new_node;
}


// Free the memory occupied by the Node
// Returns pointer to the next Node
// Returns NULL if Node *next is NULL.
Node *removeNode(Node *n)
{
	Node *next_node = n->next;
	free(n);
	return next_node;
}


// Creates new node with specified data and inserts
//	it after the Node *after.
//	Node *next pointers will be updated.
//
// If Node *after is NULL - does nothing and returns NULL
// Return NULL on failure
// Return pointer to new node on success
Node *insertAfter(NodeDataType data, Node *after)
{
	if (!after)
		return NULL;

	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->data = data;
	new_node->next = after->next;
	after->next = new_node;

	return new_node;
}
