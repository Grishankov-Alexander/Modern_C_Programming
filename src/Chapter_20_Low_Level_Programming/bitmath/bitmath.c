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
		_Pragma("GCC diagnostic push");
		_Pragma("GCC diagnostic ignored \"-Wparentheses\"");
		ui1 =	0xaa |	// 3) 10101010 | 10011100 = 10111110
			0xcc ^	// 2) 11001100 ^ 01010000 = 10011100
			0xf0 &	// 1)11110000 & 01010101 = 01010000
			0x55;
		printBinary(&ui1, sizeof ui1, true);
		_Pragma("GCC diagnostic pop");

	}


	{
		PRINT_TOPIC(Accessing bits);

		uint8_t us1 = 0;

		// Set bit 4 to 1;
		us1 |= 1 << 4;
		printBinary(&us1, sizeof us1, true);

		// Unset bit 4
		us1 &= ~(1 << 4);
		printBinary(&us1, sizeof us1, true);

		// Toggle bits 0, 3 and 5
		us1 ^= 1 + 8 + 32;
		printBinary(&us1, sizeof us1, true);

		// Test for bits 0 or 2
		if (us1 & (1 | 4))
			printf("bit 0 or 2 is set\n");

		// Test for bits 0 and 3
		if ((us1 & (1 | 8)) == (1 | 8))
			printf("bits 0 and 3 are set\n");
	}


	{
		PRINT_TOPIC(Bit Fields);
	}

	return 0;
}
