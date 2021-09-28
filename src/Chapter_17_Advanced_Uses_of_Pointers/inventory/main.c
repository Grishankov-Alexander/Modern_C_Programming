/*
 * Parts inventory
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node.h"
#include "sllist.h"


char *createString(const char *s);


int main(void)
{
	SLList l = newList();
	NodeDataType part1 = {.id = 1, .on_hand = 99, .name = createString("Part 1")};
	l.addNode(&l, part1);
	if (l.findNode(&l, part1))
		printf("Node with id %d exists!\n", part1.id);
	l.clearList(&l);

	return 0;
}


char *createString(const char *s)
{
	char *new_str = malloc(strlen(s) + 1);
	if (!new_str)
		return NULL;

	strcpy(new_str, s);

	return new_str;
}
