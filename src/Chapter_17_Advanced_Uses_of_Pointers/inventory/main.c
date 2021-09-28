/*
 *
 * Program that manages parts inventory
 * using singly-linked list.
 *
 * typedef struct part {int id; int on_hand; char *name; } NodeDataType 
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node.h"
#include "sllist.h"


#define PART_NAME_LENGTH 25


typedef SLList Inventory;
typedef NodeDataType Part;


static Inventory inv;



/*
 * Inventory functions
*/

void addPart(void);
void changePartQuantity(void);
void findPart(void);
void printParts(void);
void removePart(void);


int main(void)
{
	char command;

	inv = newList();

	printf("\n++++ Inventory managing program ++++\n\n");
	printf("List of commands:\n");
	printf("\tq - quit, a - add part, c - change part quantity,\n");
	printf("\ti - show part info, r - remove part, p - print parts\n");
	for ( ; ; ) {
		printf("\nEnter command: ");

		if (!scanf(" %c", &command))
			continue;

		while (getchar() != '\xA')
			;

		switch (command) {
			case 'q':
				return 0;
			case 'a':
				addPart();
				break;
			case 'c':
				changePartQuantity();
				break;
			case 'i':
				findPart();
				break;
			case 'r':
				removePart();
				break;
			case 'p':
				printParts();
				break;
		}
	}
}





void removePart(void)
{
	Node *n;
	Part p;

	printf("Enter Id: ");
	if (!scanf("%d", &p.id)) {
		printf("Wrong Id!\n");
		return;
	}

	if (!(n = inv.findNode(&inv, p)))
		printf("Part with id '%d' not found!", p.id);
	else
		inv.removeNode(&inv, n);
}


void printParts(void)
{
	Node *n = NULL;
	Part p = {0};

	for (n = inv.head; n; n = n->next) {
		p = n->data;
		printf("Part %d: %s [%d]\n", p.id, p.name, p.on_hand);
	}
}


void findPart(void)
{
	Part p = {0};
	Node *n = NULL;

	printf("Enter Id: ");
	if (!scanf("%d", &p.id)) {
		printf("Wrong Id!\n");
		return;
	}

	if (!(n = inv.findNode(&inv, p))) {
		printf("Part with Id '%d' doesn't exist.\n", p.id);
		return;
	}

	p = n->data;
	printf("\nPart %d: %s [%d]\n", p.id, p.name, p.on_hand);
}


void changePartQuantity(void)
{
	Part p = {0};
	Node *n = NULL;
	int change;

	printf("Enter Id: ");
	if (!scanf("%d", &p.id)) {
		printf("Wrong Id!\n");
		return;
	}

	if (!(n = inv.findNode(&inv, p))) {
		printf("Part with Id '%d' doesn't exist.\n", p.id);
		return;
	}

	printf("Enter quantity change: ");
	scanf("%d", &change);

	n->data.on_hand += change;
}


void addPart(void)
{
	Part p = {0};
	Node *n = NULL;
	char name[PART_NAME_LENGTH + 1], c, *np = name;

	printf("Enter Id: ");
	scanf("%d", &p.id);

	// Exit if id exists
	if (inv.findNode(&inv, p)) {
		printf("Part with Id '%d' already exists.\n", p.id);
		return;
	}

	// Skip newline
	while (getchar() != '\xA')
		;

	printf("Enter Part name: ");

	c = getchar();
	while (c != '\xA' && c != '\n') {
		if (np - name < PART_NAME_LENGTH)
			*np++ = c;
		c = getchar();
	}
	*np = 0;

	// Allocate memory on heap for part name
	p.name = malloc(strlen(name) + 1);
	strcpy(p.name, name);

	printf("Enter quantity: ");
	scanf("%d", &p.on_hand);

	// Find placement for the new part based on ID
	n = inv.findBigger(&inv, p);
	// It is the bigges part
	if (!n)
		inv.addNode(&inv, p);
	else
		inv.insertBefore(&inv, p, n);
}


#ifndef NODE_H
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

// Returns pointer to Node whose data is bigger than data argument
// Returns NULL if not found
Node * (*findBigger) (SLList *self, NodeDataType data)

// Remove all nodes from the list *self
// If self is NULL - do nothing
void (*clearList) (SLList *self);

// Remove specified node *n from the list *self
// if n is NULL - do nothing
// if self is NULL - do nothing
void (*removeNode) (SLList *self, Node *n);
#endif
