/*
 * Manage parts inventory.
*/


#include <stdio.h>

#include "inventory.h"
#include "part.h"
#include "readln.h"


#define STRING_LENGTH 20


int main(void)
{
	/*
	 * Ask for command
	 * Enter command
	 * p - print
	 * u - update quanitiy
	 * s - print part
	 * i - insert part
	 * q - quit
	*/

	char command;
	int part_number, on_hand, change;
	char *part_name;

	for ( ; ; ) {
		printf("\ni - insert part\ns - find part\nu - update quantity\n"
			"p - print all parts\nq - quit\nEnter command: ");

		// Scan for command, skip anything else until \n
		scanf(" %c", &command);
		while (getchar() != '\n')
			;

		switch (command) {
			case 'p':
				printf("Your inventory\n");
				print_inventory();
				break;

			case 'u':
				printf("Enter part number: "); scanf("%d", &part_number);
				printf("Enter change: "); scanf("%d", &change);
				if (update_on_hand(part_number, change) < 0)
					printf("Error! part with number %d doesn't exist\n",
						part_number);
				break;

			case 's':
				printf("Enter part number: "); scanf("%d", &part_number);
				if (search(part_number) < 0)
					printf("Error! part with number %d doesn't exist\n",
						part_number);
				break;

			case 'i':
				printf("Enter part number: "); scanf("%d", &part_number);
				printf("Enter part name: "); readln(&part_name, STRING_LENGTH + 1);
				printf("Enter quantity: "); scanf("%d", &on_hand);
				struct part new_part = {
					.number = part_number,
					.name = part_name,
					.on_hand = on_hand
				};
				if (insert_part(&new_part) < 0)
					printf("Error! Not enough space "
						"or part with number %d already exists\n",
						part_number);
				break;

			case 'q':
				clean_inventory();
				return 0;

			default:
				  printf("Wrong command\n");
				  break;
		}
	}

	return 0;
}
