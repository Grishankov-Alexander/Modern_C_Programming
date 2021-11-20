/*
 * Idiomatic program that uses File-Positioning functions
 * to clear the quantity of parts in an inventory.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>





#define FILE_NAME		"inventory.dat"
#define INITIAL_INV_SIZE	26
#define MALLOC_STEP		64
#define FWRITE_ERR		-1






typedef struct {
	size_t number;		/* Part number */
	size_t quantity;	/* Part quantity */
	char name[];		/* Part name */
} Part;







/*
 * Read Part from stream.
 *
 * Return Part on the heap.
 * Return NULL on failure
*/
Part *
readPart(FILE *stream);


/*
 * Write Part *p into stream
 *
 * Return 0 on success.
 * Return nonzero on failure.
*/
int
writePart(const Part *p, FILE *stream);








int main(void)
{
	Part **inventory;
	size_t num_parts;
	FILE *fp;

	inventory = NULL;
	fp = fopen(FILE_NAME, "rb+");

	/* Create simple inventory file if it doesn't exist */
	if (!fp) {
		size_t num = 'A';
		size_t qty = 'a';
		char name[2]= {'A', '\0'};

		// Create same amount of Part * as letters in English.
		inventory = malloc(sizeof(*inventory) * INITIAL_INV_SIZE);
		if (!inventory)
			return 1;

		/*
		 * Populate inventory with simple data.
		 * Each Part will represent a letter (A...Z)
		 * Each Part member will store Part letter (A...Z)
		*/
		for (num_parts = 0; num_parts < INITIAL_INV_SIZE; num_parts++) {
			/* Allocate space for Part and 2 chars at the end. ("A"..."Z") */
			inventory[num_parts] = malloc(sizeof(**inventory) + 2);
			/* Free all memory and exit on memory allocation failure */
			if (!inventory[num_parts]) {
				while (num_parts > 0)
					free(inventory[--num_parts]);
				free(inventory);
				return 1;
			}

			inventory[num_parts]->number = num++;
			inventory[num_parts]->quantity = qty++;
			strcpy(inventory[num_parts]->name, name);
			name[0]++;
		}

		/* Write resulting inventory into the file */
		fp = fopen(FILE_NAME, "wb+");
		/* I don't want to check if file is opened. */
		for (num_parts = 0; num_parts < INITIAL_INV_SIZE; num_parts++) {
			/* If write error occurs - free all memory and exit */
			if (writePart(inventory[num_parts], fp)) {
				while (num_parts < INITIAL_INV_SIZE)
					free(inventory[num_parts++]);
				free(inventory);
				remove(FILE_NAME);
				return 1;
			}
			free(inventory[num_parts]);
		}
		free(inventory);
	}

	fclose(fp);

	return 0;
}







/*
 * Read Part from stream
 *
 * Return Part on the heap.
 * Return NULL on failure
*/
Part *
readPart(FILE *stream)
{
	size_t a[2];		/* Stores part number and quantity */
	char *p_name;		/* Stores part name */
	size_t chars_read;	/* Index p_name */
	fpos_t file_pos;
	int c;
	Part *p;

	p_name = NULL;
	p = NULL;
	chars_read = 0;

	/* Restore file position on error */
	fgetpos(stream, &file_pos);

	/* Read part number and quantity */
	if (fread(a, sizeof(*a), sizeof(a) / sizeof(*a), stream) != 2) {
		fsetpos(stream, &file_pos);
		return NULL;
	}

	/*
	 * Read part name. Very tricky part!
	 * It doesn't check for EOF because
	 * Part will always have a name.
	*/
	do {
		/* Realloc if not enough memory */
		if (chars_read % MALLOC_STEP == 0) {
			char *new_mem;
			new_mem = realloc(p_name, chars_read + MALLOC_STEP);
			if (!new_mem) {
				free(p_name);
				fsetpos(stream, &file_pos);
				return NULL;
			}
			p_name = new_mem;
		}
		p_name[chars_read++] = c = fgetc(stream);
	} while (c != 0);

	/* Construct Part on the heap */
	p = malloc(sizeof(a) + chars_read);
	if (!p) {
		free(p_name);
		fsetpos(stream, &file_pos);
		return NULL;
	}

	/* Copy data into p */
	p->number = a[0];
	p->quantity = a[1];
	strcpy(p->name, p_name);

	free(p_name);

	return p;
}


/*
 * Write Part *p into stream
 *
 * Return 0 on success.
 * Return nonzero on failure.
*/
int
writePart(const Part *p, FILE *stream)
{
	fpos_t file_pos;

	fgetpos(stream, &file_pos);
	/* Write number, quantity and name */
	if (fwrite(p, sizeof(*p) + strlen(p->name) + 1, 1, stream))
		return 0;
	fsetpos(stream, &file_pos);
	return FWRITE_ERR;
}
