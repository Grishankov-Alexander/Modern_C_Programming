/*
 * Stack declarations
*/


#ifndef STACK_H
#define STACK_H


#include "boolean.h"


#define STACK_SZ 69


extern double stack[STACK_SZ];
extern double *head;

double pop(void);
void push(double d);
Bool is_empty(void);
Bool is_full(void);
void make_empty(void);

void stack_overflow(void);
void stack_underflow(void);


#endif /* #ifndef STACK_H */
