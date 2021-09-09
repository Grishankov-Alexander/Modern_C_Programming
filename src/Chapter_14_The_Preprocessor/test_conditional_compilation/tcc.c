/*
 * File for testing conditional compilation
*/


#include <stdio.h>


#define PRINT_TOPIC(s) \
	printf("\n\n" s "\n----------\n")


int main(void)
{
	{
		PRINT_TOPIC("#if #endif");

#define DEBUG 1
#if DEBUG
		printf("DEBUG = %d\n", DEBUG);
#endif

#undef DEBUG
#if !DEBUG
		printf("DEBUG not defined\n");
#endif
	}


	{
		PRINT_TOPIC("#defined operator");

#if !defined(DEBUG)
		printf("DEBUG macro not defined\n");
#endif

#define DEBUG
#if defined DEBUG
		printf("DEBUG macro defined\n");
#endif
#undef DEBUG
	}


	{
		PRINT_TOPIC("#ifdef and #ifndef");
	}


	return 0;
}
