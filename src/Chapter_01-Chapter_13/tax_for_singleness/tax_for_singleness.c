/*
 * Program that computes tax for being a single person
*/


#include <stdio.h>


float tax(float income)
{
	float t;

	if (income < 750.00f)
	    t = income * 0.01f;
	else if (income < 2250.00f)
	    t = income * 0.02f + 7.50f;
	else if (income < 3750.00f)
	    t = income * 0.03f + 37.50f;
	else if (income < 5250.00f)
	    t = income * 0.04f + 82.50f;
	else if (income < 7000.00f)
	    t = income * 0.05f + 142.50f;
	else
	    t = income * 0.06f + 230.00f;

	return t;
}

int main(void)
{
    float income;

    printf("Enter income: $");
    scanf("%f", &income);

    printf("Tax for being single is $%.2f\n", tax(income));

    return 0;
}
