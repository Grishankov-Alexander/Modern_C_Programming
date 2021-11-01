/*
 * Exercises from the chapter 20.
*/


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


#define SWAP(x, y)		{x ^= y; y ^= x; x ^= y;}
#define MK_COLOR(R, G, B)	((B) << 16 | (G) << 8 | (R))
#define GET_RED(COLOR)		((COLOR) & 0xff)
#define GET_GREEN(COLOR)	((COLOR) >> 8 & 0xff)
#define GET_BLUE(COLOR)		((COLOR) >> 16 & 0xff)


#define NUM_BITS(obj)	(sizeof(obj) << 3)


// Change endianness for object with specified address and size
void *
reverseBytes(void *byte, size_t num_bytes);

/*
 * Shift number i left by num_shifts bits.
 * Shifted bits will move to the right end.
*/
unsigned int
shiftLeft(unsigned int i, unsigned char num_shifts);

/*
 * Shift number i right by num_shifts bits.
 * Shifted bits will move to the left end.
*/
unsigned int
shiftRight(unsigned int i, unsigned char num_shifts);


int main(void)
{
	{
		uint8_t i, j, k;
		uint32_t big_endian_num;
		uint32_t color;
		uint32_t num;

		i = 8, j = 9;
		printf("%u\n", i >> (1 + j) >> 1);

		i = 1;
		printf("%u\n", i & ~i);

		i = 2, j = 1, k = 0;
		printf("%u\n", (~i & j) ^ k);

		i = 7, j = 8, k = 9;
		printf("%u\n", i ^ (j & k));

		SWAP(i, j);
		printf("i = %u, j = %u\n", i, j);

		color = MK_COLOR(9, 6, 15);
		printf(
			"Red = %u, Green = %u, Blue = %u\n",
			GET_RED(color), GET_GREEN(color), GET_BLUE(color)
		);

		big_endian_num = 0x78563412;
		printf(
			"After reversing: 0x%X\n",
			*(uint32_t *) reverseBytes(&big_endian_num, sizeof big_endian_num)
		);

		num = 0x12345678;
		printf("0x%X\n", num = shiftRight(num, 12));
		printf("0x%X\n", num = shiftLeft(num, 44));
	}


	return 0;
}


// Change endianness for object with specified address and size
void *reverseBytes(void *start, size_t num_bytes)
{
	typedef unsigned char Byte;

	Byte *p_first, *p_last;

	p_first = start;
	p_last = p_first + num_bytes;
	num_bytes /= 2;

	while (num_bytes--) {
		*p_first ^= *--p_last;
		*p_last ^= *p_first;
		*p_first++ ^= *p_last;
	}

	return start;
}


/*
 * Shift number i left by num_shifts bits.
 * Shifted bits will move to the right end.
*/
unsigned int
shiftLeft(unsigned int i, unsigned char num_shifts)
{
	return (i << (num_shifts % NUM_BITS(i))) | (i >> (NUM_BITS(i) - (num_shifts % NUM_BITS(i))));
}

/*
 * Shift number i right by num_shifts bits.
 * Shifted bits will move to the left end.
*/
unsigned int
shiftRight(unsigned int i, unsigned char num_shifts)
{
	return shiftLeft(i, NUM_BITS(i) - (num_shifts % NUM_BITS(i)));
}
