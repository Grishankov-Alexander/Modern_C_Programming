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

#if 1
		printf("#if 1 - True\n");
#endif

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
#ifndef DEBUG
		printf("DEBUG not defined\n");
#define DEBUG
#ifdef DEBUG
		printf("DEBUG defined\n");
#undef DEBUG
#endif /* #ifdef DEBUG */
#endif /* #ifndef DEBUG */
	}


	{
		PRINT_TOPIC("#elif and #else");

#define DEBUG_MODE_3

#ifdef NO_DEBUG
#else
	#if defined DEBUG_MODE_1
		printf("DEBUG mode: 1\n");
	#elif defined DEBUG_MODE_3
		#undef DEBUG_MODE_3
		#define DEBUG_MODE_2
		printf("Disabled DEBUG mode: 3\n");
		printf("Enabled DEBUG mode: 2\n");
	#elif !defined DEBUG_MODE_2
		#define DEBUG_MODE_2
		printf("Enabled DEBUG mode: 2\n");
	#endif /* #if defined DEBUG_MODE_1 */
#endif /* #ifdef NO_DEBUG */

	}


	return 0;
}
