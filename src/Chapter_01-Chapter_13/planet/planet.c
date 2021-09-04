/*
 * Checks whether command line argument is a planet name
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define NUM_PLANETS 9


static char *planets[NUM_PLANETS] = {
	"Mercury", "Venus", "Earth",
	"Mars", "Jupiter", "Saturn",
	"Uranus", "Neptune", "Pluto"
};


// Compare case insensitive
static int mystricmp(const char *s1, const char *s2);


int main(int argc, char *argv[])
{
	char **p, **q;

	for (p = argv + 1; p < argv + argc; p++) {
		for (q = planets; q < planets + NUM_PLANETS; q++)
			if (mystricmp(*p, *q) == 0)
				printf("%s is a planet number %ld\n",
					*p, q - planets + 1);
	}

	return 0;
}


int mystricmp(const char *s1, const char *s2)
{
	int diff;

	for ( ; ; s1++, s2++) {
		diff = tolower(*s1) - tolower(*s2);
		if (diff != 0 || *s1 == 0)
			break;
	}

	return diff;
}
