/*
 * File used for testing purposes of macros
*/


#include <stdio.h>


// Simple macros
#define DOUBLE_QUOTE "\""
#define CONTINUATION_TEST "THIS \
			IS" \
		"A SIMPLE" \
	"STRING" /* I was just curious what will happen to tabs*/


// Parameterized macros
#define MAX(x, y) ((x) > (y) ? (x) : (y)) /* Returns the biggger number*/
#define IS_EVEN(x) ((x) % 2 == 0) /* Returns 1 if x is even */
#define TOUPPER(c) ('a' <= (c) && (c) <= 'z' ? (c) - 'a' + 'A' : (c)) /* convert to uppercase */


// The # unary macro operator
#define PRINT_INT(x) printf(#x " = %d\n", x) /* prints int macro parameter */
#define STRINGIDIZE(x) #x /* Creates a string from macro parameter */
#define PRINT_STR(s) printf("%s", #s) /* Prints macro parameter as a string */
#define QUOTE_STR(s) PRINT_STR(#s) /* Prints macro parameter in quotes as a string */


// The ## binary macro operator
#define MK_ID(x) i##x /* Creates identifier ix from parameter x */
#define GENERIC_MAX(type) \
	type type##_max(type x, type y) \
	{ \
		return x > y ? x : y; \
	} \
	typedef type type##_max_t /*
		 * Define max function for the type
		 * specified as macro parameter.
		 * Also define dummy typename so
		 * we can freely put
		 * colon at the end of a macro.
	 */


// Creating longer macros
#define ECHO(s) ( \
	printf("Enter your string: "), \
	fgets((s), sizeof (s), stdin), \
	fputs((s), stdout) \
) /* Uses a comma to separate expressions */
#define COMPOUND_ECHO(s) { \
	printf("Enter your string: "); \
	fgets((s), sizeof (s), stdin); \
	fputs((s), stdout); \
} /*
   * Can be dangerous if macro will be used with semicolon
   * COMPOUND_ECHO(..);
   */
#define COMPOUND_DOWHILE_ECHO(s) do { \
	printf("Enter your string: "); \
	fgets((s), sizeof (s), stdin); \
	fputs((s), stdout); \
} while (0) /*
             * Can be dangerous it macro will be used without semicolon.
             * COMPOUND_DOWHILE_ECHO(...)
             */


// Defines a function double_max and type double_max_t
GENERIC_MAX(double);


int main(void)
{
	// Simple macros
	{
		printf(
			"\n\n"
			"Simple macros"
			"\n----------\n"
		);

		printf("%s\n", DOUBLE_QUOTE CONTINUATION_TEST DOUBLE_QUOTE);
	}


	// Parameterized macros
	{
		printf(
			"\n\n"
			"Parameterized macros"
			"\n----------\n"
		);

		printf("%d\n", MAX(2 + 3, 3 + 3));
		printf("%d, %d\n", IS_EVEN(1), IS_EVEN(2));
		printf("%c\n", TOUPPER('z'));
	}


	// The # operator - unary
	{
		printf(
			"\n\n"
			"The # unary operator"
			"\n----------\n"
		);

		PRINT_INT(5 / 3);
		printf("%s\n", STRINGIDIZE(1 + 2 + 3 + 4));
		QUOTE_STR(quoted text);
	}


	// The ## operator - binary
	{
		printf(
			"\n\n"
			"The ## binary operator"
			"\n----------\n"
		);

		int MK_ID(1) = 33, MK_ID(2) = 22, MK_ID(3) = 11;
		printf("i1 = %d, i2 = %d, i3 = %d\n",
			MK_ID(1), MK_ID(2), MK_ID(3));

		printf("%.2lf\n", double_max(2.0, 3.0));
	}


	// Creating longer macros
	{
		printf(
			"\n\n"
			"Createing longer macros"
			"\n----------\n"
		);

		char a[10];
		ECHO(a);
		COMPOUND_ECHO(a);
		COMPOUND_DOWHILE_ECHO(a);
	}

	return 0;
}
