/*
 * Reads n - 1 characters from the input line into s.
 * Skips initial whitespaces.
 * Returns number of characters read
*/


#ifndef READLN_H
#define READLN_H


// Reads at max n - 1 characters from the line into allocated memory.
// Changes *s to point to a new location.
// Returns number of characters read.
int readln(char **s, int n);


#endif /* #ifndef READLN_H */
