/*
 *
 * For testing Storage Classes.
*/




/*
 * Storage duration:
 * 	1) Static - Variable stays at the same storage location
 * 	as long as the program is running.
 * 	2) Auto - Storage allocated when surrounding block is executed.
 * 	Storage deallocated when the block terminates.
 *
 * Scope:
 * 	1) Block scope - Variable is visible from its point
 * 	of declaration to the end of the block.
 * 	2) File scope - Variable is visible from its point
 * 	of declaration to the end of the file.
 *
 * Linkage:
 * 	1) No linkage - Variable belongs to a block
 * 	and can't be shared.
 * 	2) Internal linkage - Variable belongs to a single file,
 * 	can be shared by functions in that file.
 * 	3) External linkage - May be shared to other files in the program.
 *
 * ? - This sign will be used later in regards to the extern variable.
 * 	When variable declared as extern it linkage can vary:
 * 	1) Internal - if the variable was declared static earlier in the file
 * 	2) External - otherwise.
*/




#include <stdio.h>


// Ignore unused varialble warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"




// Static storage duration, file scope, ?.
extern int i1;
// Static storage duration, file scope, external linkage.
int i1;
// Static storage duration, file scope, internal linkage.
static int i2;
// Static storage duration, file scope, internal linkage.
extern int i2;
// Static storage duration, file scope, external linkage.
extern int i1;

// Static storage duration, file scope, external linkage.
void f1(void);
// Static storage duration, file scope, external linkage.
extern void f2(void);
// Static storage duration, file scope, internal linkage.
static void f3(void);


int i6 = 6;
static int i7 = 7;
// i1 - auto storage duration, block scope, no linkage
// i2 - auto storage duration, block scope, no linkage
// Note on i2: compiler might or might not put i2 in the CPU register.
// 	&i2 is illegal operation.
int *f4(int i1, register int i2)
{
	// auto storage duration, block scope, no linkage
	auto int i3;
	// static storage duration, block scope, no linkage.
	static int i4;
	// static storage duration, block scope, ?
	extern int i5;
	// static storage duration, block scope, external linkage
	extern int i6;
	// static storage duration, block scope, internal linkage
	extern int i7;

	printf("i6 = %d\n", i6);
	printf("i7 = %d\n", i7);

	// It's possible to write to i4 outside this block.
	return &i4;
}




// Stop ignoring unused variable
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop




int main(void)
{
	int *p = f4(0, 0);

	return 0;
}
