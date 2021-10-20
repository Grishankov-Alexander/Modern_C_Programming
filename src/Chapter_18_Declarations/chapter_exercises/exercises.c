/*
 * Exercises from the chapter.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MEMDUMP(obj)						\
{								\
	unsigned char *p;					\
	for (	p = (unsigned char *) &(obj);			\
		p < (unsigned char *) &(obj) + sizeof (obj);	\
		p++	)					\
			printf("%-3.2x", *p);			\
	printf("\n");						\
}

#define PI 3.14159


// f1 is a function that takes int and
// returns pointer to an allocated array of 5 ints that have value i
int (* f1(int i))[5]
{
	int (*p)[5], *q;
	p = malloc(sizeof *p);

	for (q = *p; (int (*)[5]) q < p + 1; q++)
		memcpy(q, &i, sizeof i);

	return p;
}
// Same as above:
typedef int (*Five_Int_Arr_Ptr)[5];
Five_Int_Arr_Ptr (*f1_alt)(int i) = f1;


// Copies value of i into static float variable.
// Returns address of static float variable.
float *f2(int i) {
	static float f; memcpy(&f, &i, sizeof i); return &f;
}


// f3 is a function
// that takes no arguments
// and returns a pointer to a function
// that takes int
// and returns pointer to float
float *(* f3(void))(int) { return f2; }
// Same as above
typedef float * (*Fnc_Ptr_Int_Float_Ptr)(int);
Fnc_Ptr_Int_Float_Ptr (*f3_alt)(void) = f3;


// f4 is a function
// that takes int i
// and pointer to function pf
// that takes int
// and returns void
// and returns pointer to function
// that takes int
// and returns void
// Awesome innit ?
void (* f4(int i, void (*pf)(int)))(int)
{
	printf("Calling (*pf)(%d)\n", i);
	(*pf)(i);
	return pf;
}
// Same as above
typedef void (*Fnc_Ptr_Int_Void)(int);
Fnc_Ptr_Int_Void (*f4_alt)(int, Fnc_Ptr_Int_Void) = f4;


// a1 is an array of pointers to functions
// that take double
// and return int
extern int (*a1[])(double);


// f5 is an extern function
// that takes pointer to function
//	that takes long
//	and returns float
// and pointer to char
// and returns pointer to function
// 	that takes double
// 	and returns int
extern int (*f5(float (*)(long), char *))(double);


// We can only use constants when declaring
// variables with static storage duration
static int i = 5, j = PI;
double d = PI;


int main(void)
{
	{
		int (*p1)[5];

		p1 = f1(0xAB);
		MEMDUMP(*p1);
		free(p1);
	}

	{
		float *p_f;

		p_f = f3()(0x89ABCDEF);
		MEMDUMP(*p_f);
	}


	// To get rid of unused variable warnings
	i -= j, j -= i, d -= i;

	return 0;
}
