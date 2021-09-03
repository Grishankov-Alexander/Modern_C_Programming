/*
 * File containing string functions and statements
 * to test strings
*/


#include <string.h>
#include <stdio.h>
#include <ctype.h>


// Return number of characters in string s
static size_t mystrlen(const char *s);

// Concantenate s2 into s1. Return s1
static char *mystrcat(char *s1, const char *s2);

// Concatenate n characters from s2 into s1. Return s1
static char *mystrncat(char *s1, const char *s2, int n);

// Copy s2 int s1. Return s1
static char *mystrcpy(char *s1, const char *s2);

// Copy n characters of s2 into s1. Return s1
static char *mystrncpy(char *s1, const char *s2, int n);

// Read n characters from input line into s1. Return number of characters read.
static int readln(char *s1, int n);

// Compare string s1 to s2.
// if s1 < s2 returns negative.
// if s1 > s2 returns positive.
// if s1 == s2 returns zero
static int mystrcmp(const char *s1, const char *s2);

// Capitalize all letters in the string
static char *mystrcap(char *s);

// Replace every occurence of substring subs with reps in string s
static char *mystrreplace(char *s, const char *subs, const char *reps);


int main(void)
{
	char s1[10] = "", s2[4] = "abc";

	// Returns 3
	mystrlen(s2);
	// s1 == "abc"
	mystrcat(s1, s2);
	// s1 == "abcab"
	mystrncat(s1, s2, 2);
	// s1 == "abcababca"
	mystrncat(s1, s1, sizeof(s1) - mystrlen(s1) - 1);
	// copy empty string into s1
	mystrcpy(s1, "");
	// s1 will become {'a', 'b', 'c'}
	mystrncpy(s1, "abc", 3);
	// result of mystrlen(s1) will be 9
	printf("mystrlen(s1) == %zu\n", mystrlen(s1));
	// compare strings
	{
		char s1[] = "a";
		char s2[] = "aa";
		printf("mystrcmp(\"%s\", \"%s\") == %d\n",
			s1, s2, mystrcmp(s1, s2));
	}
	// Read line into s2
	printf("Enter a line: ");
	readln(s2, sizeof(s2) - 1);
	printf("s2 = %s\n", s2);
	// capitalize all characters of s1
	mystrcpy(s1, "abc");
	printf("%s\n", mystrcap(s1));

	// Test substring replacement function
	{
		char s[100];
		char sub[25], rep[25];

		printf("Enter your string: ");
		readln(s, sizeof(s) - 1);
		printf("Enter substring that will be replaced: ");
		readln(sub, sizeof(sub) - 1);
		printf("Enter replacement string: ");
		readln(rep, sizeof(rep) - 1);

		printf("\nResulting string: %s\n", mystrreplace(s, sub, rep));
	}

	return 0;
}


static size_t mystrlen(const char *s)
{
	const char *p = s;

	while (*p++)
		;

	return p - s - 1;
}


static char *mystrcat(char *s1, const char *s2)
{
	char *p = s1;
	while (*p)
		p++;
	while ((*p++ = *s2++))
		;
	return s1;
}


static char *mystrncat(char *s1, const char *s2, int n)
{
	char *p = s1;
	while (*p)
		p++;
	for ( ; n > 0 && *s2; p++, s2++, n--)
		*p = *s2;
	*p = 0;

	return s1;
}


static char *mystrcpy(char *s1, const char *s2)
{
	char *p = s1;

	while ((*p++ = *s2++))
		;

	return s1;
}


static char *mystrncpy(char *s1, const char *s2, int n)
{
	char *p = s1;

	while (n > 0 && *s2) {
		*p++ = *s2++;
		n--;
	}

	return s1;
}


static int readln(char *s1, int n)
{
	char c;
	int i = 0;

	while ((c = getchar()) != '\n' && c != EOF) {
		if (i < n)
			s1[i++] = c;
	}

	s1[i] = '\0';

	return i;
}


static int mystrcmp(const char *s1, const char *s2)
{
	for ( ; *s1 == *s2; s1++, s2++) {
		if (!*s1)
			return 0;
	}
	return *s1 - *s2;
}


static char *mystrcap(char *s)
{
	char *p = s;
	while (*p) {
		if (isalpha(*p))
			*p = toupper(*p);
		p++;
	}

	return s;
}


static char *mystrreplace(char *s, const char *subs, const char *reps)
{
	char *p;
	const char *ps, *pr;

	for (p = s; *p; p++) {
		// Skip until char matches with first substring char
		if (*p != *subs)
			continue;
		// Check whether substring is matched
		for (p += 1, ps = subs + 1; *p && *ps; p++, ps++)
			if (*p != *ps)
				break;
		// Move p to where it was
		p -= ps - subs;
		// Chars don't match or s reached the end
		if ((size_t) (ps - subs) < strlen(subs))
			continue;
		// Replace substring with new string
		for (pr = reps; *p && *pr; p++, pr++)
			*p = *pr;
		// Point p to last replaced char if the replacement string was not empty
		if (pr - reps)
			p--;
	}

	return s;
}
