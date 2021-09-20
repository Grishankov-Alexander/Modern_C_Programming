/*
 * Q&A and Chapter Exercises
*/


#include <stdio.h>


#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n----------\n")
#define CHAR_POINTER(obj) ((char *) &(obj))
#define MEMDUMP(obj) \
	printf(#obj " dump:"); \
	for (char *p = CHAR_POINTER(obj); p < CHAR_POINTER(obj) + sizeof (obj); p++) \
		printf("%3.2x", *p & 0xFF); \
	printf("\n");


int main(void)
{
	// Q & A
	{
		PRINT_TOPIC(Q & A);

		enum weekdays {
			MONDAY,
			TUESDAY,
			WEDNESDAY,
			THURSDAY,
			FRIDAY,
		};

		const char *daily_specials[] = {
			[MONDAY]	= "Beef ravioli",
			[TUESDAY]	= "BLTs",
			[WEDNESDAY]	= "Pizza",
			[THURSDAY]	= "Chicken fajitas",
			[FRIDAY]	= "Macaroni and cheese",
		};
		
		printf("%s\n", daily_specials[FRIDAY]);
	}


	// Exercises
	{
		PRINT_TOPIC(Exercieses);

		struct {
			double real;
			double imag;
		} c1 = {.imag = 1.0}, c2 = {1.0}, c3;

		MEMDUMP(c1);
		c1 = c2;
		c3.real = c1.real + c2.real;
		c3.imag = c1.imag + c2.imag;
		c1 = c3;
	}

	return 0;
}
