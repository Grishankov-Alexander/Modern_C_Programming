/*
 * For trying out complex declarations.
*/


#include <stdio.h>


// x is array of 10 pointers to functions
// that take void and return int *
int *(* x[10])(void) = {NULL};

// We can simplify this declaration using typedefs
typedef int *Fnc(void);
typedef Fnc *Fnc_Ptr;
typedef Fnc_Ptr Fnc_Ptr_Arr[10];


Fnc_Ptr_Arr y = {NULL};


int main(void)
{
	printf("%p\n%p\n", (void *) x, (void *) y);

	return 0;
}
