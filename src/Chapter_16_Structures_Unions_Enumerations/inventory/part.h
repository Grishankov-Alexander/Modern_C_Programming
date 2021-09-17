/*
 * Part structure holds information:
 * - Part number
 * - Part name
 * - number of this part on hand
*/


#ifndef PART_H
#define PART_H


struct part {
	int number;
	char *name;
	int on_hand;
};


void print_part(const struct part *p);


#endif /* #ifndef PART_H */
