/*
 * Q&A and Chapter Exercises
*/


#include <stdio.h>
#include <stdbool.h>


#define PRINT_TOPIC(...) \
	printf("\n\n" #__VA_ARGS__ "\n----------\n")
#define CHAR_POINTER(obj) ((char *) &(obj))
#define MEMDUMP(obj) \
	printf(#obj " dump:"); \
	for (char *p = CHAR_POINTER(obj); p < CHAR_POINTER(obj) + sizeof (obj); p++) \
		printf("%3.2x", *p & 0xFF); \
	printf("\n");
// WhyTF does this work
#define VAL_TO_TYPE(value, type) \
	*(type *) (__typeof__(value)[]) {(value)}


struct complex {
	double real;
	double imag;
};

struct date {
	int day;
	int month;
	int year;
};

struct time {
	int h;
	int m;
	int s;
};

struct color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};


// Returns struct complex created from real r and imaginary i
struct complex make_complex(double r, double i);
// Adds real and imaginary of c1 and c2 and returns new complex
struct complex add_complex(const struct complex *c1, const struct complex *c2);
// Returns the day of year
int day_of_year(const struct date *d);
// Returns -1 id d1 is earlier than d2. 0 if same. +1 otherwise
int datecmp(const struct date *d1, const struct date *d2); 
// Split into struct with members - hours, minutes, seconds
struct time split_time(long long total_seconds);

// Create color from rgb
struct color make_color(unsigned char r, unsigned char g, unsigned char b);
bool equal_color(struct color c1, struct color c2);
struct color darker(struct color c);
struct color brighter(struct color c);
void print_color(struct color c);


int main(void)
{
	// Q & A
	{
		PRINT_TOPIC(Q & A);

		enum weekdays {
			MONDAY,
			TUESDAY,
			WEDNESDAY,
			THURSDAY,
			FRIDAY,
		};

		const char *daily_specials[] = {
			[MONDAY]	= "Beef ravioli",
			[TUESDAY]	= "BLTs",
			[WEDNESDAY]	= "Pizza",
			[THURSDAY]	= "Chicken fajitas",
			[FRIDAY]	= "Macaroni and cheese",
		};
		
		printf("%s\n", daily_specials[FRIDAY]);
	}


	// Exercises
	{
		PRINT_TOPIC(Exercieses);

		struct complex c1 = {.imag = 1.0}, c2 = {1.0}, c3;

		MEMDUMP(c1);
		c1 = c2;
		c3.real = c1.real + c2.real;
		c3.imag = c1.imag + c2.imag;

		c3 = add_complex(&c3, &c3);
		c3 = make_complex(
			VAL_TO_TYPE(0x0123456789abcdef, double),
			VAL_TO_TYPE(0x0123456789abcdef, double)
		);
		MEMDUMP(c3);

		struct time t1 = split_time(90129);
		printf("%.2d:%.2d:%.2d\n", t1.h, t1.m ,t1.s);
	}


	// Colors
	{
		PRINT_TOPIC(Colors);

		struct color c = {255, 0, 148};
		c = brighter(c);
		print_color(c);
	}


	return 0;
}


struct complex make_complex(double r, double i)
{
	return (struct complex) {
		.real = r,
		.imag = i,
	};
}


struct complex add_complex(const struct complex *c1, const struct complex *c2)
{
	return (struct complex) {
		.real = c1->real + c2->real,
		.imag = c1->imag + c2->imag,
	};
}


int day_of_year(const struct date *d)
{
	int month = d->month;
	int day = d->day;

	// In my mad world there is 31 day in each month.
	while (month-- > 1)
		day += 31;

	return day;
}


int datecmp(const struct date *d1, const struct date *d2)
{
	int res, total1, total2;

	// Looks ugly kek
	if (d1->year == d2->year) {
		if (d1->month == d2->month) {
			if (d1->day == d2->day)
				res = 0;
			else
				res = d1->day < d2->day ? -1 : 1;
		} else
			res = d1->month < d2->month ? -1 : 1;
	} else
		res = d1->year < d2->year ? -1 : 1;

	// Looks better by 10 %
	total1 = ((d1->year * 12) + (d1->month - 1)) * 31 + d1->day;
	total2 = ((d2->year * 12) + (d2->month - 1)) * 31 + d1->day;
	res = total1 < total2 ? -1 : (total1 == total2 ? 0 : 1);

	return res;
}


struct time split_time(long long total_seconds)
{
	return (struct time) {
		.h = (total_seconds / 3600) % 24,
		.m = (total_seconds % 3600) / 60,
		.s = (total_seconds % 60),
	};
}


struct color make_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (struct color) {.red = r, .green = g, .blue = b};
}


bool equal_color(struct color c1, struct color c2)
{
	return c1.red == c2.red
		&& c1.green == c2.green
		&& c1.blue == c2.blue
		? true : false;
}


struct color darker(struct color c)
{
	return (struct color) {
		.red = c.red * 0.7,
		.green = c.green * 0.7,
		.blue = c.blue * 0.7,
	};
}


struct color brighter(struct color c)
{
	unsigned char r = c.red, g = c.green, b = c.blue;

	if (r == g && g == b && b == 0)
		return make_color(3, 3, 3);

	if (0 < r && r < 3)
		r = 3;
	if (0 < g && g < 3)
		g = 3;
	if (0 < b && b < 3)
		b = 3;

	r = r / 0.7 > 255 ? 255 : r / 0.7;
	g = g / 0.7 > 255 ? 255 : g / 0.7;
	b = b / 0.7 > 255 ? 255 : b / 0.7;

	return make_color(r, g, b);
}


void print_color(struct color c)
{
	printf(" R   G   B \n" "%-4.3d%-4.3d%-4.3d\n", c.red, c.green, c.blue);
}
