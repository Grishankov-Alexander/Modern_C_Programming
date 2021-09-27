/*
 * Node declarations
*/


#ifndef NODE_H
#define NODE_H


#ifndef NODE_DATA_TYPE
#define NODE_DATA_TYPE struct part {int id; int on_hand; char *name;}
#endif /* #ifndef NODE_DATA_TYPE */


typedef NODE_DATA_TYPE NodeDataType;
typedef struct node Node;


struct node {
	NodeDataType data;
	Node *next;
};


/*
 * Public functions on node
*/

// Creates new node on the heap.
// Return NULL on failure
// Return pointer no new Node on success.
Node *newNode(NodeDataType data);

// Free the memory occupied by the Node
// Returns pointer to the next Node
// Returns NULL if Node *next is NULL.
Node *removeNode(Node *n);

// Creates new node with specified data and inserts
//	it after the Node *after.
//	Node *next pointers will be updated.
//
// If Node *after is NULL - does nothing and returns NULL
// Return NULL on failure
// Return pointer to new node on success
Node *insertAfter(NodeDataType data, Node *after);


#endif /* #ifndef NODE_H */
