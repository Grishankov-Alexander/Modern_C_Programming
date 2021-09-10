/*
 * File used for testing purposes of macros
*/


#include <stdio.h>
#include <string.h>


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
#define PRINT_TOPIC_NAME(s) \
	printf("\n\n" s "\n" "----------" "\n") /* Print topic header */
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


// Predefined macros
#define PRINT_COMPILATION_INFO \
	printf("Program was compiled on %s at %s\n", __DATE__, __TIME__);
#define TEST_ZERO(x) \
	if (!(x)) \
		printf("Divizion by zero in file %s on line %d\n", \
			__FILE__, __LINE__)


// Empty Macro arguments
#define ADD(x, y) (x + y)
#define MAKE_STR(x) #x
#define JOIN_TOKENS(x, y) x##y


// Macros with a variable number of arguments
#define PRINTF(...) printf(__VA_ARGS__)
#define IF_FALSE(condition, ...) \
	((condition) \
	 ? fputs(#condition "\n", stdout) \
	 : __VA_ARGS__) /* Evaluate expressions that follow condition
			     if condition is false
			     */


// The __func__identifier
#define PRINT_FUNC_NAME printf("Function name: %s\n", __func__)
#define NOTIFY_FUNC_RETURN(x) printf("Function %s returns %s.\n", __func__, #x)


// Defines a function double_max and type double_max_t
GENERIC_MAX(double);


int main(void)
{
	// Simple macros
	{
		PRINT_TOPIC_NAME("Simple macros");

		printf("%s\n", DOUBLE_QUOTE CONTINUATION_TEST DOUBLE_QUOTE);
	}


	// Parameterized macros
	{
		PRINT_TOPIC_NAME("Parameterized macros");

		printf("%d\n", MAX(2 + 3, 3 + 3));
		printf("%d, %d\n", IS_EVEN(1), IS_EVEN(2));
		printf("%c\n", TOUPPER('z'));
	}


	// The # operator - unary
	{
		PRINT_TOPIC_NAME("The # unary operator");

		PRINT_INT(5 / 3);
		printf("%s\n", STRINGIDIZE(1 + 2 + 3 + 4));
		QUOTE_STR(quoted text);
	}


	// The ## operator - binary
	{
		PRINT_TOPIC_NAME("The ## binary operator");

		int MK_ID(1) = 33, MK_ID(2) = 22, MK_ID(3) = 11;
		printf("i1 = %d, i2 = %d, i3 = %d\n",
			MK_ID(1), MK_ID(2), MK_ID(3));

		printf("%.2lf\n", double_max(2.0, 3.0));
	}


	// Creating longer macros
	{
		PRINT_TOPIC_NAME("Createing longer macros");

		//char a[10];
		//ECHO(a);
		//COMPOUND_ECHO(a);
		//COMPOUND_DOWHILE_ECHO(a);
	}


	// Predefined macros
	{
		PRINT_TOPIC_NAME("Predefined macros");

		PRINT_COMPILATION_INFO;
		int j = 0;
		TEST_ZERO(j);
#ifdef __STDC__
		printf("__STDC__ = %d\n", __STDC__);
#endif
	}


	// Empty macro arguments
	{
		PRINT_TOPIC_NAME("Empty Macro Arguments");

		int n = ADD(2, 3);
		printf("%d\n", n);
		n = ADD( , 3);
		printf("%d\n", n);
		char a[] = MAKE_STR(Hello world!\n);
		printf("%s", a);
		strcpy(a, MAKE_STR());
		printf("%s", a);
		int JOIN_TOKENS(var, _1) = 1;
		int JOIN_TOKENS(var_2, ) = 2;
		printf("%d\n", var_1 - var_2);
	}


	// Macros with a variable number of arguments
	{
		PRINT_TOPIC_NAME("Macros with a variable number of arguments");

		PRINTF("This %s %s %s %s\n", "works", "same", "as", "printf");
		int x = 5, y = 3;
		IF_FALSE(x > y, printf("y >= x\n"));
		IF_FALSE(y > x, printf("%d <= %d\n", y, x));
	}


	// The __func__ identifier
	{
		PRINT_TOPIC_NAME("The __func__ identifier");

		PRINT_FUNC_NAME;
		NOTIFY_FUNC_RETURN(0);
	}


	// Advanced concepts
	{
		PRINT_TOPIC_NAME("Advanced concepts");

		/*
		 * Idea of the following example:
		 * When macro expands, it evaluates inner macros first if they exist
		 *
			* TO_STR(abc TO_STR(def))
			* -> STRINGIZE(abc TO_STR(def))
			* -> STRINGIZE(abc STRINGIZE(def))
			* -> STRINGIZE(abc "def")
			* -> "abc \"def\""
		*/
#		define STRINGIZE(x) #x
#		define TO_STR(x) STRINGIZE(x)
		printf("TO_STR(abc TO_STR(def)) = %s\n", TO_STR(abc TO_STR(def)));

		/* Same thing works for token concat */
#		define TOKENIZE(x, y) x##y
#		define CONCAT_TOKENS(x, y) TOKENIZE(x, y)
		int CONCAT_TOKENS(a, CONCAT_TOKENS(b, c)) = (unsigned) ~0 >> 1;
		printf("abc = %d\n", abc);

		/*
		 * Idea of the following example:
		 * 1) Macro can't call itself recursively
		 * 2) If Macro "A" called macro "B", and macro "B" contains
		 * 	calls to macro "A", calls from "B" to "A" will not expand
		 *
			* BAZ
			* -> TO_STR(PRINT_FOO)
			* -> TO_STR(PRINT_BAR "FOO" PRINT_BAR PRINT_FOO)
			* -> TO_STR(PRINT_FOO "BAR" PRINT_FOO "FOO" PRINT_BAR PRINT_FOO)
			* -> TO_STR(PRINT_FOO "BAR" PRINT_FOO "FOO" PRINT_FOO "BAR" PRINT_FOO PRINT_FOO)
			* -> "PRINT_FOO \"BAR\" PRINT_FOO \"FOO\" PRINT_FOO \"BAR\" PRINT_FOO PRINT_FOO"
		*/
#		define PRINT_FOO PRINT_BAR "FOO" PRINT_BAR PRINT_FOO
#		define PRINT_BAR PRINT_FOO "BAR" PRINT_FOO
#		define BAZ TO_STR(PRINT_FOO)
		printf("BAZ = %s\n", BAZ);
	}

	return 0;
}
