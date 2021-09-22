/*
 * Operations on rectangle on a graphics screen.
*/


#include <stdbool.h>
#include <stdio.h>


struct point {
	int x;
	int y;
};

struct rectangle {
	struct point upper_left;
	struct point lower_right;
};


// Helper function to return positive length of the side.
static inline int length(int x1, int x2);

static inline int area(const struct rectangle *r);
static struct point center(const struct rectangle *r);
static void move(struct rectangle *r, int x, int y);
// Does the point lies within rectangle
static bool within(const struct rectangle *r, struct point p);
static void print_rectangle(const struct rectangle *r);


int main(void)
{
	struct rectangle r = {
		{-4, 2},
		{2, -4},
	};

	print_rectangle(&r);
	printf("Area: %d\n", area(&r));
	printf("Center point: %d, %d\n", center(&r).x, center(&r).y);
	printf("%d\n", within(&r, (struct point) {-3, 1,}));
	move(&r, 4, 4);
	print_rectangle(&r);
}


static inline int length(int x1, int x2)
{
	int l = x2 - x1;
	return l < 0 ? -l : l; 
}


static inline int area(const struct rectangle *r)
{
	return length(r->lower_right.x, r->upper_left.x)
		* length(r->lower_right.y, r->upper_left.y);
}


static struct point center(const struct rectangle *r)
{
	int half_length_x = length(r->lower_right.x, r->upper_left.x) / 2;
	int half_length_y = length(r->lower_right.y, r->upper_left.y) / 2;

	return (struct point) {
		.x = r->upper_left.x + half_length_x,
		.y = r->lower_right.y + half_length_y,
	};
}


static void move(struct rectangle *r, int x, int y)
{
	r->upper_left.x += x;
	r->upper_left.y += y;
	r->lower_right.x += x;
	r->lower_right.y += y;
}


static bool within(const struct rectangle *r, struct point p)
{
	return r->upper_left.x <= p.x && p.x <= r->lower_right.x
		&& r->lower_right.y <= p.y && p.y <= r->upper_left.y;
}


static void print_rectangle(const struct rectangle *r)
{
	int i;

	// Little ugly formatting :)
	printf("%3d, %-3d", r->upper_left.x, r->upper_left.y);
	printf(" ___________ \n");
	for (i = 0; i < 3; i++)
		printf("%8c%-12c%c\n", ' ', '|', '|');
	printf("%8c%c___________%c%3d, %-3d\n\n", ' ', '|', '|', r->lower_right.x, r->lower_right.y);
}
