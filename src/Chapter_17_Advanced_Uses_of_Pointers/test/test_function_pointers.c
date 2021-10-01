/*
 * Concepts related to function pointers.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// Prints topic name
#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n==========\n")




// For testing "qsort"
struct part {
	int id;
	char *name;
};




// Helper Functions
void printParts(const struct part *inv, size_t nmemb);




// For testing "function pointers as arguments"
void printDouble(void *);
void incrementDouble(void *);
void foreach(void *base, size_t nmemb, size_t szmemb, void (*f) (void *));
// void (*f) (void *) is same as void f (void *)




// For testing "qsort"
int cmpById(const void *p, const void *q);
int cmpByName(const void *p, const void *q);




// For testing "Other uses of function pointers"
//
// Calls function (*mathfn) with arguments
// from first to last using specified increment value.
void
tabulate(
	double (*mathfn) (double),
	double first, double last,
	double increment
);




int main(void)
{
	// Function pointers as arguments
	{
		PRINT_TOPIC(Function pointers as arguments);

		double ad[] = {1.01, 2.02, 3.03};

		foreach(ad, sizeof ad / sizeof *ad, sizeof *ad, printDouble);
		// printDouble is same as &printDouble
		foreach(ad, sizeof ad / sizeof *ad, sizeof *ad, &incrementDouble);
		foreach(ad, sizeof ad / sizeof *ad, sizeof *ad, printDouble);
	}


	// qsort
	{
		PRINT_TOPIC(qsort);

		/*
		 * qsort prototype:
		 * void qsort(void *base, size_t nmemb, size_t szmemb,
		 * 		int (*cmp) (const void *p, const void *q))
		*/

		struct part inv[] = {
			{3, "HDD"},
			{2, "SSD"},
			{1, "GPU"},
		};

		printf("Initial inventory:\n");
		printParts(inv, sizeof inv / sizeof *inv);

		qsort(inv, sizeof inv / sizeof *inv, sizeof *inv, cmpById);
		printf("\nSorted by id:\n");
		printParts(inv, sizeof inv / sizeof *inv);

		qsort(inv, sizeof inv / sizeof *inv, sizeof *inv, cmpByName);
		printf("\nSorted by name:\n");
		printParts(inv, sizeof inv / sizeof *inv);
	}


	// Other uses of Function Pointers
	{
		PRINT_TOPIC(Other uses of Function Pointers);

		double d = 2.09;

		// As Variable
		void (*vf) (void *) = printDouble;

		// As Array variable
		void (*vfa[]) (void *) = {
			vf,
			printDouble,
			incrementDouble,
		};

		// Accessing array of function pointers
		(*vfa)(&d);
		// Same as above
		vfa[0](&d);
		// Yet Another way of writing this
		(*vfa[1])(&d);
		// And one more
		(*(vfa + 1))(&d);

		printf(
			"\n"
			"  x        sin(x)\n"
			"-----      ------\n"
		);
		tabulate(sin, .62, .72, .03);

		/*
		 * Super obscure use of function pointers
		 *
		 * Couldn't resist.
		*/
	}


	/*
	 * Super obscure declaration of function pointer
	 * Couldn't resist.
	 *
	 *
	 * The general rule of C (and C++) declarations is:
	 * if you type the declaration as an expression,
	 * it will have the declaration's type
	 *
	 * fp is a pointer to function
	 * that takes pointer to function
	 * that takes char
	 * and returns int8_t
	 * and returns pointer to function
	 * that takes int16_t
	 * and returns pointer to function
	 * that takes float
	 * and returns double
	*/
	double (* (* (*fp) (int8_t (*) (char))) (int16_t)) (float);

	return 0;
}




void foreach(void *base, size_t nmemb, size_t szmemb, void (*f) (void *))
{
	char *p;

	for (p = base; p < (char *) base + nmemb * szmemb; p += szmemb)
		(*f)(p);
		// (*f)(p) is same as f(p)
}


void printDouble(void *p)
{
	printf("%lg\n", *(double *) p);
}


void incrementDouble(void *p)
{
	*(double *) p += 1;
}


int cmpById(const void *p, const void *q)
{
	return ((struct part *) p)->id - ((struct part *) q)->id;
}


int cmpByName(const void *p, const void *q)
{
	return strcmp(((struct part *) p)->name, ((struct part *) q)->name);
}


void printParts(const struct part *inv, size_t nmemb)
{
	const struct part *p;

	for (p = inv ; p < inv + nmemb; p++)
		printf("%d: %s\n", p->id, p->name);
}


void
tabulate(
	double (*mathfn) (double),
	double first, double last,
	double increment
)
{
	double res, curr;
	int i, num_steps;

	num_steps = ceil((last - first) / increment);
	for (i = 0; i <= num_steps; i++) {
		curr = first + i * increment;
		res = (*mathfn)(curr);
		printf("%5lg%6s%lg\n", curr, "", res);
	}
}
