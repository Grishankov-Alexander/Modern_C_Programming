#include <stdlib.h>

#include "part.h"
#include "inventory.h"


static struct part inventory[INVENTORY_SIZE];
static int num_parts = 0;


// Returs index of part with part_number. -1 on failure
static int find_part(int part_number);


// Inserts new part into inventory. Return index on success. -1 on failure
int insert_part(const struct part *p)
{
	int index;
	index = find_part(p->number);
	if (index >= 0 || num_parts >= INVENTORY_SIZE)
		return -1;
	inventory[num_parts] = (struct part) {
		.number = p->number,
		.name = p->name,
		.on_hand = p->on_hand
	};

	return num_parts++;
}

// Prints data for part with part_number. -1 if not exists
int search(int part_number)
{
	int index;
	index = find_part(part_number);
	if (index < 0)
		return -1;
	print_part(inventory + index);
	return index;
}

// Adds change to quantity of part with_number. Returs -1 on failure
int update_on_hand(int part_number, int change)
{
	int index;

	index = find_part(part_number);
	if (index < 0)
		return -1;
	inventory[index].on_hand += change;

	return index;
}

// Prints all parts in inventory
void print_inventory(void)
{
	const struct part *p;

	for (p = inventory; p < inventory + num_parts; p++)
		print_part(p);
}


// Returs index of part with part_number. -1 on failure
static int find_part(int part_number)
{
	const struct part *p;

	for (p = inventory; p < inventory + num_parts; p++)
		if (p->number == part_number)
			return p - inventory;
	return -1;
}

// Free allocated memory
void clean_inventory(void)
{
	int i;
	for (i = 0; i < num_parts; i++)
		free(inventory[i].name);

	num_parts = 0;
}
