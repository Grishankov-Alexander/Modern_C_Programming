/*
 * Example usage of doubly-linked list.
*/


#include "dllist.h"

#include <stddef.h>


int main(void)
{
	// Inits list
	Node *head = insert(5.557, NULL);
	// Inserts at the beginning.
	head = insert(2.225, NULL);
	// Appends to the end
	Node *tail = append(8.922);
	// Inserts before tail
	Node *new_node = insert(6.3, tail);
	// prints the list
	print_list();

	remove_node(new_node);
	new_node = NULL;
	print_list();

	remove_node(head);
	head = NULL;
	print_list();

	clear_list();
	tail = NULL;
	print_list();

	return 0;
}
