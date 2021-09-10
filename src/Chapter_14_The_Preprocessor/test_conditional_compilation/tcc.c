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
#endif /* #if DEBUG */

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
	/* ... */
#else
#	if defined DEBUG_MODE_1
		printf("DEBUG mode: 1\n");
#	elif defined DEBUG_MODE_3
#		undef DEBUG_MODE_3
#		define DEBUG_MODE_2
		printf("Disabled DEBUG mode: 3\n");
		printf("Enabled DEBUG mode: 2\n");
#	elif !defined DEBUG_MODE_2
#		define DEBUG_MODE_2
		printf("Enabled DEBUG mode: 2\n");
#	endif /* #if defined DEBUG_MODE_1 */
#endif /* #ifdef NO_DEBUG */
	}


	{
		PRINT_TOPIC("#error, #line and #pragma");
#define OS_LINUX
#ifdef OS_WIN
	/* ... */
#elif defined OS_LINUX
	/* ... */
#else
	#error OS not supported
#endif
#undef OS_LINUX

#line __LINE__ "foo.c"
		printf("Filename: %s, Line: %d\n", __FILE__, __LINE__);

/* Pragma directive to print specified message on compilation */
#pragma message "Compiling file " __FILE__ 
		/* Same as above but using _Pragma operator */
		_Pragma("message \"Compiling file \" __FILE__");
#define DO_PRAGMA(x) _Pragma(#x)
		/* Same but using macro expansion */
		DO_PRAGMA(message "Compiling file " __FILE__);
	}


	return 0;
}
