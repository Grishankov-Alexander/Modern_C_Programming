/*
 * Shape structure and operations on it.
*/


#include <stdio.h>


#define PI 3.14159265
#define SQUARE(x) ((x) * (x))


struct point {
	int x, y;
};

struct shape {
	enum {CIRCLE, RECTANGLE,} kind; // 4 bytes
	struct point center; // 8 bytes
	union {
		struct {
			int width, height;
		} rectangle;
		struct {
			int radius;
		} circle;
	} shape; // 8 bytes
} s;


// Functions on shape
void print_shape(const struct shape *s)
{
	switch (s->kind) {
		case CIRCLE:
			printf("__________\n" "Shape: Circle\nRadius:"
				"%d\nCenter: %d, %d\n",
				s->shape.circle.radius,
				s->center.x, s->center.y);
			break;
		case RECTANGLE:
			printf("__________\n" "Shape: Rectangle\nWidth:"
				"%d\nHeight: %d\nCenter: %d, %d\n",
				s->shape.rectangle.width,
				s->shape.rectangle.height,
				s->center.x, s->center.y);
			break;
	}
}


int area(const struct shape *s)
{
	int area = 0;

	switch (s->kind) {
		case RECTANGLE:
			area = s->shape.rectangle.width
				* s->shape.rectangle.height;
			break;
		case CIRCLE:
			area = SQUARE(s->shape.circle.radius) * PI;
			break;
	}

	return area;
}


struct shape *move(struct shape *s, int x, int y)
{
	s->center.x += x;
	s->center.y += y;

	return s;
}


struct shape *scale(struct shape *s, double c)
{
	switch (s->kind) {
		case CIRCLE:
			s->shape.circle.radius *= c;
			break;
		case RECTANGLE:
			s->shape.rectangle.width *= c;
			s->shape.rectangle.height *= c;
			break;
		default:
			break;
	}

	return s;
}


int main(void)
{
	struct shape c = {
		.kind = CIRCLE,
		.center = {0, 0},
		.shape.circle.radius = 5,
	};
	struct shape r = {
		.kind = RECTANGLE,
		.center = {0, 0},
		.shape.rectangle.width = 5,
		.shape.rectangle.height = 10,
	};

	print_shape(&c), print_shape(&r);
	printf("Circle area: %d, Rectangle area: %d\n", area(&c), area(&r));
	print_shape(scale(&c, 3.5)), print_shape(scale(&r, 2.9));
	print_shape(move(&c, -3, 9)), print_shape(move(&r, 5, -4));
}
