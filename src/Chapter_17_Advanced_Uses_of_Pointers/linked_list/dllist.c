/*
 * Doubly linked list
*/


#include "dllist.h"

#include <stdlib.h>
#include <stdio.h>


// Node head and tail
static Node *HEAD = NULL;
static Node *TAIL = NULL;


// Initializes list with first node.
// HEAD == TAIL == returned new node.
static Node *init_first_node(datatype v);

// Adds new node as a new HEAD.
// Returns NULL on failure.
static Node *insert_head(datatype v);




// Initializes list with first node.
// HEAD == TAIL == returned new node.
// Returns NULL on allocation failure
static Node *init_first_node(datatype v)
{
	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->value = v;
	new_node->prev = NULL;
	new_node->next = NULL;

	HEAD = new_node;
	TAIL = new_node;

	return new_node;
}


// Adds new node as a new HEAD.
// Returns NULL on failure.
static Node *insert_head(datatype v)
{
	if (!HEAD)
		return init_first_node(v);

	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->value = v;
	new_node->prev = NULL;
	new_node->next = HEAD;
	HEAD->prev = new_node;
	HEAD = new_node;

	return new_node;
}


// Append Node with value v at the end.
// Return pointer to New Node or NULL on failure
Node *append(datatype v)
{
	if (!TAIL)
		return init_first_node(v);

	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->value = v;
	new_node->next = NULL;
	new_node->prev = TAIL;
	TAIL->next = new_node;
	TAIL = new_node;

	return new_node;
}


// Insert new node before Node n.
// If n is NULL - insert at the beginning. Return pointer to the new node
// Return Null on failure.
Node *insert(datatype v, Node *n)
{
	if (!n)
		n = HEAD;

	if (n == HEAD)
		return insert_head(v);

	Node *new_node = malloc(sizeof *new_node);
	if (!new_node)
		return NULL;

	new_node->value = v;
	new_node->prev = n->prev;
	new_node->next = n;
	n->prev->next = new_node;
	n->prev = new_node;

	return new_node;
}


// Search list for Node with value v. Return pointer to Node with value v.
// Return Null if v not found
Node *search(datatype v)
{
	Node *p;

	for (p = HEAD; p && p->value != v; p = p->next)
		;

	return p;
}


// Remove Node n from the list
void remove_node(Node *n)
{
	if (!n) {
		return;
	} else if (n == HEAD) {
		if (n->next) {
			n->next->prev = NULL;
			HEAD = n->next;
		}
		else {
			HEAD = TAIL = NULL;
		}
	} else if (n == TAIL) {
		TAIL = n->prev;
		TAIL->next = NULL;
	} else {
		n->next->prev = n->prev;
		n->prev->next = n->next;
	}

	free(n);
}


// Clears the list of nodes. Resets HEAD and TAIL.
void clear_list(void)
{
	Node *p;

	while (HEAD) {
		p = HEAD->next;
		free(HEAD);
		HEAD = p;
	}

	TAIL = NULL;
}


// Prints contents of the doubly-linked list
void print_list(void)
{
	Node *p = HEAD;
	int counter = 1;

	printf("\n\nResulting list\n==========\n");

	while (p) {
		printf("Node %d (address: %p)\n" "\tvalue: %lg\n" "\tprev: %p\n" "\tnext: %p\n\n",
			counter++, (void *) p, p->value, (void *) p->prev, (void *) p->next);
		p = p->next;
	}
}
