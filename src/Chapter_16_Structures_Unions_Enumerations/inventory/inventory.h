/*
 * Contains Database that stores parts.
 * Provides operations on working with database.
*/


#ifndef INVENTORY_H
#define INVENTORY_h


#define INVENTORY_SIZE 100


struct part;

// Inserts new part into inventory. Return index on success. -1 on failure
int insert_part(const struct part *p);

// Prints data for part with part_number. -1 if not exists
int search(int part_number);

// Adds change to quantity of part with_number. Returs -1 on failure
int update_on_hand(int part_number, int change);

// Prints all parts in inventory
void print_inventory(void);

// Frees memory allocated
void clean_inventory(void);


#endif /* #ifndef INVENTORY_H */
