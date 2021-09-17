#include <stdio.h>

#include "part.h"


void print_part(const struct part *p)
{
	printf("%d %s %d\n", p->number, p->name, p->on_hand);
}
