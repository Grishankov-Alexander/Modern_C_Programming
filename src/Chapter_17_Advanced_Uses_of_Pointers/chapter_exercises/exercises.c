/*
 * Chapter 17 Exercises.
*/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n==========\n")


/*
 * My wrapper around realloc.
 * If failure - free previously allocated memory and exit
 *
 * case 1: prevalloc 0, bytes 0 // dummy call - LET IT BE. Returns not NULL
 * case 2: prevalloc 1, bytes 0 // freeing - LET IT BE. Returns NULL;
 * case 3: prevalloc 0, bytes 1 // allocate - exits on failure
 * case 4: prevalloc 1, bytes 1 // reallocate - free prev and exit on failure
*/
void *myMalloc(void *prevalloc, size_t bytes);

void testMyMalloc(void);

// Allocate memory, copy str into it, return memory allocated.
char *newStr(const char *str);

// Allocate memory for the array that has nmemb members of size szmemb.
// Use *init to initialize every member
void *newArray(const void *init, size_t nmemb, size_t szmemb);


// Passing function pointer to a function
int f1(int (*f) (int));
int f2(int i);


// Revised function from exercise 13.
// Should insert nodes by ascending value.
// Real good implementation kek.
struct node {int value; struct node *next;};
struct node *insertOrdered(struct node *list, struct node *new);




int main(void)
{
	// My malloc wrapper
	{
		PRINT_TOPIC(malloc wrapper);

		char *mystr;

		mystr = myMalloc(NULL, 0); // Allocates dummy memory. mystr != NULL
		mystr = myMalloc(mystr, 0); // Frees memory. Set mystr to NULL
		mystr = myMalloc(NULL, 1024); // Usual malloc
		mystr = myMalloc(mystr, 2048); // Reallocates
		mystr = myMalloc(mystr, 0);
		//testMyMalloc();

		printf("mystr: %s", mystr = newStr("Hello world!\n"));
		mystr = myMalloc(mystr, 0);
	}


	// Allocate and initialize array
	{
		PRINT_TOPIC(Allocate and initialize array);

		size_t n = 3;

		int *a = newArray(&(int){3}, n, sizeof *a);

		for (int *p = a; p < a + n; p++)
			printf(" %d", *p);
		printf("\n");

		myMalloc(a, 0);
	}


	{
		struct point {
			int x, y;
		};

		struct rectangle {
			struct point upper_left, lower_right;
		};

		struct rectangle *p = myMalloc(NULL, sizeof *p);
		p->upper_left = (struct point) {10, 25};
		p->lower_right = (struct point) {20, 15};

		myMalloc(p, 0);
	}


	// Passing function pointer to a function
	{
		PRINT_TOPIC(Passing function pointer to a function);

		printf("%d\n", f1(f2));
	}


	{
	}


	return 0;
}



void *myMalloc(void *prevalloc, size_t bytes)
{
	void *new;

	new = realloc(prevalloc, bytes);

	if (!new && bytes) {
		if (prevalloc)
			free(prevalloc);
		printf(	"\nAllocation failed. Exit status: FAILURE.\n"
			"\tmyMalloc(%p, %zu)\n", prevalloc, bytes);
		exit(EXIT_FAILURE);
	}

	return new;
}


void testMyMalloc(void)
{
	char *mystr = NULL;
	size_t sz = 1024UL;

	do {
		printf("myMalloc(%p, %zu)\n", (void *) mystr, sz);
		mystr = myMalloc(mystr, sz);
		memset(mystr, 0xff, sz);
		sz *= 16UL;
	} while (mystr);
}


char *newStr(const char *str)
{
	return strcpy(myMalloc(NULL, strlen(str) + 1), str);
}


void *newArray(const void *init, size_t nmemb, size_t szmemb)
{
	void *a = myMalloc(NULL, nmemb * szmemb);

	if (!init) {
		memset(a, '\x0', nmemb * szmemb);
		return a;
	}

	for (char *p = a; p < (char *) a + nmemb * szmemb; p += szmemb)
		memcpy(p, init, szmemb);

	return a;
}


int f1(int (*f) (int))
{
	int n = 0;

	while ((*f)(n)) n++;

	return n;
}


int f2(int i)
{
	return i * i + i - 12;
}


struct node *insertOrdered(struct node *list, struct node *new)
{
	struct node **listptr;

	for (listptr = &list; *listptr; listptr = &(*listptr)->next)
		if ((*listptr)->value > new->value)
			break;

	new->next = *listptr;
	*listptr = new;

	return list;
}
