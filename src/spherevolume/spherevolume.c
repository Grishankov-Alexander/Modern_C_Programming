/*
 * Program that computes volume of a sphere
 * given a user specified radius
*/

#include <stdio.h>

#define SPHERE_RATIO (4.0f / 3.0f)
#define PI 3.14159f

int main(void)
{
	float radius, volume;

	printf("Specify the radius: ");
	(void)scanf("%f", &radius);

	volume = SPHERE_RATIO * PI * (radius * radius * radius);
	
	printf("Spere volume: %.3f\n", volume);

	return 0;
}
