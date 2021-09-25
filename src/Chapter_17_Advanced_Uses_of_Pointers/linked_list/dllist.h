/*
 * Doubly linked list
*/


#ifndef DLLIST_H
#define DLLIST_H


#ifndef DLLIST_DATATYPE
#define DLLIST_DATATYPE double
#endif


// Typedef
typedef DLLIST_DATATYPE datatype;

// Struct node
typedef struct node Node;
struct node {
	datatype value;
	Node *prev;
	Node *next;
};


// Append Node with value v at the end.
// Return pointer to New Node or NULL on failure
Node *append(datatype v);

// Insert new node in place of n. Move n and other nodes up.
// If n is NULL - insert at the beginning. Return pointer to New Node
// Return NULL on failure.
Node *insert(datatype v, Node *n);

// Search list for Node with value v. Return pointer to Node with value v.
// Return Null if v not found
Node *search(datatype v);

// Remove Node n from the list
void remove_node(Node *n);

// Clears the list of nodes. Resets HEAD and TAIL.
void clear_list(void);

// Prints contents of the doubly-linked list
void print_list(void);


#endif /* #ifndef DLLIST_H */
