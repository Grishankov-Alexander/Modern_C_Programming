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


	{
		PRINT_TOPIC(Bit Fields and Structures);

		struct storage {
			unsigned int a : 5;	// 5 bits (from 0 to 31)
			unsigned int b : 4;
			unsigned int : 8;	// Padding 8 bits
			signed int c : 7;	// 7 bits (from -64 to 63)
			int : 0;		// Break paddind (skip until the end of allocation unit)
			unsigned int d : 32;	// May not work if unsigned int takes less than 32 bits
		};

		struct storage s;
		// &s.a = illegal operation
		s.a = 0x11;	// 10001
		s.b = 0x9;	// 1001
		s.c = -63;	// 1000001
		s.d = ~0;	// All ones

		printBinary(&s, sizeof s, true);


		// Next operations assume Little-Endian storage.
		unsigned int *field = (void *) &s;
		// Overwrite s.a to 01110
		*field = (*field & ~(0x1f)) | (0xE);
		// Overwrite s.b to 0110
		*field = (*field & ~(0xF << 5)) | (0x6 << 5);
		// Toggle s.c
		*field ^= 0x7F << 17;
		// Switch to the next bit field and toggle it
		*++field ^= ~0;

		printBinary(&s, sizeof s, true);
	}


	{
		PRINT_TOPIC(Multiple views of data with unions);

		typedef unsigned char Byte;
		typedef uint16_t Word;

		struct date {
			Word day : 5, month : 4, year : 7;
		};

		union fast_date{
			Word _dt;
			struct date dt;
		};

		struct date dt = {.day = 0x1, .month = 0x3, .year = 0x7F};
		union fast_date fdt = {0xFFFF};
		fdt = *(union fast_date *) &dt;

		printBinary(&dt, sizeof dt, true);
		printBinary(&fdt, sizeof fdt, true);

		union {
			struct {
				Word ax, bx, cx, dx;
			} words;
			struct {
				Byte al, ah, bl, bh, cl, ch, dl, dh;
			} bytes;
		} registers;

		registers.bytes.al = 0xF7;
		registers.bytes.ah = 0x7F;

		printBinary(&registers.words.ax, sizeof registers.words.ax, true);
	}


	{
		PRINT_TOPIC(Volatile Type Qualifier);

		typedef unsigned char Byte;

		// p is a pointer to a volatile byte.
		// Basically informs the compiler
		// that contents of memory can be easily changed
		// outside this translation unit
		volatile Byte *p = (Byte *) 0x100;
		p += 1;
	}

	return 0;
}
