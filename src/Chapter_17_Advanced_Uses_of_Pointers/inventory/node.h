/*
 * Node to be used in a singly linked list
 *
 * Each node has a 'data' member.
 * The type of this member can be changed by changing this macros:
 *	NODE_DATA_TYPE - macro that defines the type of the underlying data
 *		for each node.
 *	NODE_DATA_CLEAN_FUNC - macro that defines function that will be
 *		called prior to removing node and freeing its memory.
 *	DATA_COMPARE_FUNC - macro that defines function to compare
 *		objects of NodeDataType
*/


#ifndef NODE_H
#define NODE_H


// Underlying contents of each node
#define NODE_DATA_TYPE struct part {int id; int on_hand; char *name;}

// Function to clean underlying contents to call when deleting a node.
#define NODE_DATA_CLEAN_FUNC \
void cleanNodeData(NodeDataType data) { free(data.name); }

// Function to compare two objects of type NodeDataType.
// Should Return 0 if same.
// Should Return negative if data1 < data2
// Should Return positive if data1 > data2
#define DATA_COMPARE_FUNC \
int compareData(NodeDataType data1, NodeDataType data2) { return data1.id - data2.id; }


typedef NODE_DATA_TYPE NodeDataType;


typedef struct node {
	NodeDataType data;
	struct node *next;
} Node;


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

// Macro function for comparison.
int compareData(NodeDataType data1, NodeDataType data2);


#endif /* #ifndef NODE_H */
