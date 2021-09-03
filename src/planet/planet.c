/*
 * Checks whether command line argument is a planet name
*/


#include <stdio.h>
#include <string.h>


#define NUM_PLANETS 9


static char *planets[NUM_PLANETS] = {
	"Mercury", "Venus", "Earth",
	"Mars", "Jupiter", "Saturn",
	"Uranus", "Neptune", "Pluto"
};


int main(int argc, char *argv[])
{
	char **p, **q = planets;

	for (p = argv + 1; *p != NULL; p++) {
		for (q = planets; q < planets + NUM_PLANETS; q++)
			if (strcmp(*p, *q) == 0)
				printf("%s is a planet number %ld\n",
					*p, q - planets + 1);
	}

	return 0;
}
