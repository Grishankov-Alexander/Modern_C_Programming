/*
 * Parts inventory
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sllist.h"


char *createString(const char *s);
static void removePart(NodeDataType p);


int main(void)
{
	SLList l = newList(&removePart);
	NodeDataType part1 = {.id = 1, .on_hand = 99, .name = createString("Part 1")};
	l.addNode(&l, part1);
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


static void removePart(NodeDataType data)
{
	free(data.name);
}
