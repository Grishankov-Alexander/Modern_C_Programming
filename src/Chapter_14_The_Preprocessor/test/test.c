/*
 * File for testing purposes
*/


#include <stdio.h>
#include <math.h>


#define STRINGIZE(x) #x
#define MAKE_STR(x) STRINGIZE(x)
#define PRINT_TOPIC(s) printf("%s", "\n\n" s "\n----------\n")


int main(void)
{
	/* https://stackoverflow.com/questions/12447557/can-we-have-recursive-macros */
	{
		PRINT_TOPIC("https://stackoverflow.com/questions/"
				"12447557/can-we-have-recursive-macros");

#		define EMPTY(...)
#		define EXPAND(...) __VA_ARGS__
#		define DEFER(...) __VA_ARGS__ EMPTY()
#		define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#
#		define pr_id() pr
#		define pr(n) ((n) == 1 ? 1 : DEFER(pr_id)()((n) - 1))
#		define SHOW_pr(n) MAKE_STR(pr(n))
		/*
			 * SHOW_pr(2)
			 * -> MAKE_STR(pr(2))
			 * -> MAKE_STR(((2) == 1 ? 1 : DEFER(pr_id)()((2) - 1))
			 * -> MAKE_STR(((2) == 1 ? 1 : pr_id EMPTY()()((2) - 1))
			 * -> MAKE_STR(((2) == 1 ? 1 : pr_id ()((2) - 1))
		*/
		printf("%s\n", SHOW_pr(2));
	}


	/* Make sqrt expand to 0 if argument is negative. */
	{
		PRINT_TOPIC("Make sqrt expand to 0 if argument is negative.");

#		undef sqrt
#		define sqrt(x) ((x) < 0 ? 0 : sqrt(x))
		/*
			 * sqrt(-2)
			 * -> ((-2) < 0 ? 0 : sqrt(-2))
		*/
		printf("sqrt(-2) = %.2lf\n", sqrt(-2));
		printf("sqrt(2) = %.2lf\n", sqrt(2));
	}


	/* Test topic */
	{
		PRINT_TOPIC("Test topic");

#		define TEST
		/*
			 * Test
		*/
		printf("%s\n", MAKE_STR(TEST));
	}


	return 0;
}
