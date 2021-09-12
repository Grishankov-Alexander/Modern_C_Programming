/*
 * File contains solutions for Chapter 14 Exercises
*/


#include <stdio.h>


#define STRINGIZE(...) "" #__VA_ARGS__
#define TO_STR(...) STRINGIZE(__VA_ARGS__)


static const char *return_const_str(const char *str);


int main(void)
{
#	define CUBE(x) ((x) * (x) * (x))
	printf("CUBE(3) = %d\n", CUBE(3));

#	define MOD4(x) ((x) % 4)
	printf("MOD4(15) = %d\n", MOD4(15));

#	define PRODUCT_LESS_THAN_100(x, y) ((x) * (y) < 100 ? 1 : 0)
	printf("%d\n", PRODUCT_LESS_THAN_100(88, 0.5)); 

#	define NELEMS(x) (sizeof(x) / sizeof(*(x)))
	char a[22];
	printf("NELEMS(a) = %zu\n", NELEMS(a));

#	define DOUBLE(x) (2 * (x))
	printf("4/DOUBLE(2) = %d\n", 4/DOUBLE(2));


#	define AVG(x, y) (x + y) / 2
	/*
		 * Problem 1: 3 * AVG(2, 2)
		 * -> 3 * (2 + 2) / 2
		 * -> 3 * 4 / 2
		 * -> 12 / 2
	*/
#	undef AVG
#	define AVG(x, y) (((x) + (y)) / 2)
	printf("AVG(2, 2) -> %s\n", TO_STR(AVG(2, 2)));
#	define AREA(x, y) (x) * (y)
	/*
		 * Problem 1: 4 / AREA(2, 3)
		 * -> 4 / (2) * (3)
		 * -> 2 * 3
	*/
#	undef AREA
#	define AREA(x, y) ((x) * (y))
	printf("4 / AREA(2, 3) -> %s = %d\n", TO_STR(4 / AREA(2, 3)), 4 / AREA(2, 3));

#	define TOUPPER(c) ('a' <= (c) && (c) <= 'z' ? (c) - 'a' + 'A' : (c))
	printf("TOUPPER('b') -> %s\n", TO_STR(TOUPPER('b')));

#	define CALL_F(f, ...) f(__VA_ARGS__) /* Expands to call of function f*/
#	define DISP_F_CALL(f, ...) \
		printf(STRINGIZE(f(__VA_ARGS__)) " = %s\n", \
			CALL_F(f, __VA_ARGS__))
	/*
		 * DISP_F_CALL(return_const_str, "Hello, world!")
		 * -> printf(STRINGIZE(return_const_str("Hello, world!")) " = %s\n",
		 *  		CALL_F(return_const_str, "Hello, world!"))
		 * -> printf(#return_const_str("Hello, world!") " = %s\n",
		 *  		return_const_str("Hello, world!"))
		 * -> printf("return_const_str(\"Hello, world!\")" " = %s\n",
		 *  		"Hello, world!")
	*/
	DISP_F_CALL(return_const_str, "Hello, world!");

#	define LINE_FILE TO_STR(Line: __LINE__; File:\x20) __FILE__
	/*
		 * LINE_FILE
		 * -> TO_STR(Line: __LINE__; File:\x20) __FILE__
		 * -> TO_STR(Line: 71; File:\x20) "exercises.c"
		 * -> STRINGIZE(Line: 71; File:\x20) "exercises.c"
		 * -> #Line: 71; File:\x20 "exercises.c"
		 * -> "Line: 71; File: " "exercises.c"
	*/
	printf("%s\n", LINE_FILE);

#	define CHECK(x, y, n) \
		(0 <= (x) && 0 <= (y) \
		&& (x) < n && (y) < n)
	printf("CHECK(0, 5, 6) = %d\n", CHECK(0, 5, 6));

#	define MAX(x, y) ((x) > (y) ? (x) : (y))
#	define MIN(x, y) ((x) < (y) ? (x) : (y))
#	define MEDIAN(x, y, z) ((x) > (z) && (y) > (z) ? MIN(x, y) : (MIN(MAX(x, y), z)))
	printf("MEDIAN(1, 3, 5) = %d\n", MEDIAN(1, 3, 5));

#	define POW2(x) ((x) * (x))
#	define POW3(x) (POW2(x) * (x))
#	define POW4(x) (POW2(x) * POW2(x))
#	define POW5(x) (POW3(x) * POW2(x))
#	define POLYNOMIAL(x) (3 * POW5(x) + 2 * POW4(x)	- 5 * POW3(x) - POW2(x) + 7 * (x) - 6)
	printf("POLYNOMIAL(3) = %d\n", POLYNOMIAL(3));

#	define ERROR(fmts, ...) fprintf(stderr, fmts, __VA_ARGS__)
	ERROR("Out of range. Index = %d\n", 5);

#	define PRAGMA(...) _Pragma(#__VA_ARGS__)
#	define WRITE_COMPILE_MESSAGE(...) PRAGMA(message #__VA_ARGS__)
	WRITE_COMPILE_MESSAGE(Hello, world)


	return 0;
}


static const char *return_const_str(const char *str)
{
	return str;
}
