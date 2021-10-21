/*
 * Demonstrates how Abstract Generic stack can be used
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"


int main(void)
{
	StackPtr s;
	int i;
	char *str;

	s = stackCreate();
	i = 5, stackPush(s, &i);
	i = 7, stackPush(s, &i);
	printf("%d\n", *(int *) stackPop(s));
	stackDestroy(s);

	s = stackCreate();
	strcpy(str = malloc(sizeof "world!"), "world!");
	stackPush(s, str);
	strcpy(str = malloc(sizeof "Hello, "), "Hello, ");
	stackPush(s, str);
	printf("%s", str = (char *) stackPop(s));
	free(str);
	printf("%s\n", str = (char *) stackPop(s));
	free(str);
	stackDestroy(s);

	return 0;
}
