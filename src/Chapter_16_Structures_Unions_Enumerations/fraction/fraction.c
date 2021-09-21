/*
 * Operations on fractions
 *
 * Fraction represented as a struct
*/


#include <stdio.h>
#include <stdlib.h>


// exit from the program if x is zero
#define EXIT_IF_ZERO(x) \
	if ((x) == 0) {printf("Exit cause: "#x " == 0\n"); exit(EXIT_FAILURE);}


struct fraction {
	int numerator;
	int denominator;
};


// Return positive greatest common divisor of a and b
int gcd(int a, int b);
// Returns positive common denominator
int common_denom(int a, int b);
// Reduce fraction to lowest terms
struct fraction *reduce_fr(struct fraction *fr);
// Adds a and b
struct fraction add_fr(const struct fraction *a, const struct fraction *b);
// Returns a - b
struct fraction sub_fr(const struct fraction *a, const struct fraction *b);
// Multiply a * b
struct fraction mul_fr(const struct fraction *a, const struct fraction *b);
// Divide a / b
struct fraction div_fr(const struct fraction *a, const struct fraction *b);
// Prints fraction
void print_fr(const struct fraction *fr);


int main(void)
{

	// Division
	{
		struct fraction fr1 = {
			.numerator = 2, .denominator = 3,
		};
		struct fraction fr2 = {
			.numerator = 1, .denominator = 4,
		};
		struct fraction fr3 = div_fr(&fr1, &fr2);
		print_fr(&fr3);
	}


	// Multiplication
	{
		struct fraction fr1 = {
			.numerator = 2, .denominator = -3,
		};
		struct fraction fr2 = {
			.numerator = 1, .denominator = 4,
		};
		struct fraction fr3 = mul_fr(&fr1, &fr2);
		print_fr(&fr3);
	}


	// Subraction
	{
		struct fraction fr1 = {
			.numerator = 1, .denominator = -7,
		};
		struct fraction fr2 = {
			.numerator = 4, .denominator = -2,
		};
		struct fraction fr3 = sub_fr(&fr1, &fr2);
		print_fr(&fr3);
	}


	// Sum
	{
		struct fraction fr1 = {
			.numerator = 1, .denominator = -7,
		};
		struct fraction fr2 = {
			.numerator = 4, .denominator = -2,
		};
		struct fraction fr3 = add_fr(&fr1, &fr2);
		print_fr(&fr3);
	}


	return 0;
}


int gcd(int a, int b)
{
	int amodb;

	while (b != 0) {
		amodb = a % b;
		a = b;
		b = amodb;
	}

	return a < 0 ? -a : a;
}


int common_denom(int a, int b)
{
	int cd = a;

	while (cd % b != 0)
		cd += a;

	return cd < 0 ? -cd : cd;
}


struct fraction *reduce_fr(struct fraction *fr)
{
	int div = gcd(fr->numerator, fr->denominator);
	EXIT_IF_ZERO(div);
	fr->numerator /= div;
	fr->denominator /= div;
	return fr;
}


struct fraction add_fr(const struct fraction *a, const struct fraction *b)
{
	int cd;
	struct fraction fr;

	EXIT_IF_ZERO(a->denominator);
	EXIT_IF_ZERO(b->denominator);
	cd = common_denom(a->denominator, b->denominator);
	fr.denominator = cd;
	fr.numerator = (cd / a->denominator * a->numerator) + (cd / b->denominator * b->numerator);
	reduce_fr(&fr);

	return fr;
}


struct fraction sub_fr(const struct fraction *a, const struct fraction *b)
{
	int cd;
	struct fraction fr;

	EXIT_IF_ZERO(a->denominator);
	EXIT_IF_ZERO(b->denominator);
	cd = common_denom(a->denominator, b->denominator);
	fr.denominator = cd;
	fr.numerator = (cd / a->denominator * a->numerator) - (cd / b->denominator * b->numerator);
	reduce_fr(&fr);

	return fr;
}


struct fraction mul_fr(const struct fraction *a, const struct fraction *b)
{

	struct fraction fr = {
		.numerator = a->numerator * b->numerator,
		.denominator = a->denominator * b->denominator,
	};
	reduce_fr(&fr);

	return fr;
}


struct fraction div_fr(const struct fraction *a, const struct fraction *b)
{
	struct fraction fr = mul_fr(
			a,
			&(struct fraction) {
				.numerator = b->denominator,
				.denominator = b->numerator,
			}
	);

	return fr;
}


void print_fr(const struct fraction *fr)
{
	printf("%d / %d\n", fr->numerator, fr->denominator);
}
