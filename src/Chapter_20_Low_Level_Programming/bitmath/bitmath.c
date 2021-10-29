/*
 * Discovering Bit operators.
*/


#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


#define PRINT_TOPIC(...)					\
{								\
	printf("\n\n" #__VA_ARGS__ "\n");			\
	size_t num_separators = sizeof #__VA_ARGS__;		\
	while (--num_separators)				\
		putchar('=');					\
	printf("\n");						\
}


/*
 * Print binary representation of the object.
 *
 * obj_mem	- address of the object in memory
 * obj_size	- size of the object in bytes.
 * litte_endian	- read memory from last address to first.
*/
void printBinary(void *obj_mem, size_t obj_size, bool little_endian)
{
	char *byte_mem;
	int num_bits;

	if (little_endian)
		byte_mem = (char *) obj_mem + obj_size - 1;
	else
		byte_mem = obj_mem;

	while (obj_size--) {
		num_bits = 8;

		while (num_bits--)
			putchar('0' + (*byte_mem >> num_bits & 1));
		putchar(' ');

		if (little_endian)
			byte_mem--;
		else
			byte_mem++;
	}

	putchar('\n');
}


int main(void)
{
	{
		PRINT_TOPIC(Bitwise operations);

		uint8_t ui1;
		int8_t si1;

		// Set all bits to 1
		ui1 = ~0;
		si1 = ~0;
		printBinary(&ui1, sizeof ui1, true);
		printBinary(&si1, sizeof si1, true);

		// Right shift half of the object.
		ui1 >>= sizeof ui1 * 4;
		si1 >>= sizeof si1 * 4;;
		printBinary(&ui1, sizeof ui1, true);
		printBinary(&si1, sizeof si1, true);

		// Precedency for binary operators
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
		ui1 =	0xAA |	// 3) 10101010 | 10011100 = 10111110
			0xCC ^	// 2) 11001100 ^ 01010000 = 10011100
			0xF0 &	// 1)11110000 & 01010101 = 01010000
			0x550 >> 4;
#pragma GCC diagnostic pop
		printBinary(&ui1, sizeof ui1, true);

	}


	{
		PRINT_TOPIC(Accessing individual bits);

		uint8_t ui1 = 0;

		// Set bit 4 to 1;
		ui1 |= 1 << 4;
		printBinary(&ui1, sizeof ui1, true);

		// Unset bit 4
		ui1 &= ~(1 << 4);
		printBinary(&ui1, sizeof ui1, true);

		// Toggle bits 0, 3 and 5
		ui1 ^= 1 + 8 + 32;
		printBinary(&ui1, sizeof ui1, true);

		// Test for bits 0 or 2
		if (ui1 & (1 | 4))
			printf("bit 0 or 2 is set\n");

		// Test for bits 0 and 3
		if ((ui1 & (1 | 8)) == (1 | 8))
			printf("bits 0 and 3 are set\n");
	}


	{
		PRINT_TOPIC(Accessing multiple bits);

		uint8_t ui1 = ~0, j;

		// Clear 3 bits starting from bit 4
		ui1 &= ~(0x7 << 4);
		printBinary(&ui1, sizeof ui1, true);

		// Set 3 bits starting from bit 4
		ui1 |= 0x7 << 4;
		printBinary(&ui1, sizeof ui1, true);

		// toggle 3 bits starting from bit 5
		ui1 ^= 0x7 << 5;
		printBinary(&ui1, sizeof ui1, true);

		// Modify bits 4-7 to store the value j
		j = 0xA;
		ui1 = (ui1 & ~0xF0) | (j << 4);
		printBinary(&ui1, sizeof ui1, true);

		// Retreive the value of bits 4-7 of ui1
		j = ui1 >> 4 & 0xF;
		printBinary(&j, sizeof j, true);
	}

	return 0;
}
