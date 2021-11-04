/*
 * Exercises from the chapter 20.
*/


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#define SWAP(x, y)		{x ^= y; y ^= x; x ^= y;}

#define MK_COLOR(R, G, B)	((B) << 16 | (G) << 8 | (R))
#define GET_RED(COLOR)		((COLOR) & 0xff)
#define GET_GREEN(COLOR)	((COLOR) >> 8 & 0xff)
#define GET_BLUE(COLOR)		((COLOR) >> 16 & 0xff)

#define NUM_BITS(obj)	(sizeof(obj) << 3)


/*
 * Helper Function
 *
 * Print num_bytes in HEX format
 * starting from byte *first_byte if reverse_bytes is false.
*/
static void printBytes(void *first_byte, size_t num_bytes, bool reverse_bytes)
{
	typedef unsigned char Byte;

	Byte *p =	reverse_bytes
			? (Byte *) first_byte + num_bytes - 1
			: (Byte *) first_byte;


	while (num_bytes--) {
		printf("%-3.2X", *p);
		if (reverse_bytes)	p--;
		else			p++;
	}

	printf("\n");
}


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

/*
 * Return num_bits bits starting from the starting_bit bit of i.
*/
unsigned int
selectBits(unsigned int i, uint8_t starting_bit, uint8_t num_bits);

/*
 * Return number of bits set to 1
*/
uint8_t
countOnes(unsigned int i);

/*
 * Return reversed bits of i
*/
unsigned int
reverseBits(unsigned int i);


int main(void)
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

	printf("Bits 16..23 of num: 0x%X\n", selectBits(num, 23, 8));

	printf("Number of bits set to 1 in a number 0x74: %u\n", countOnes(0x74));

	i = 0x5E;
	printf("0x5E with bits reversed = 0x%X\n", reverseBits(i));

	struct {
		signed int flag : 1;
	} s;
	s.flag = -1;
	printf("s.flag = %d\n", s.flag);

	union {
		unsigned int ieee_float;
		struct {
			unsigned int fr : 23, exp : 8, sign : 1;
		};
	} f1;

	f1.sign = 0x1;
	f1.exp = 0xEE;
	f1.fr = 0x7ABBCC;
	printBytes(&f1, sizeof f1, true);
	printf("Resulting Float = 0x%X\n", f1.ieee_float);
	printf("sign = 0x%X, exponent = 0x%X, fractional part = 0x%X\n",
		f1.sign, f1.exp, f1.fr);

	f1.ieee_float = 0x778000CD;
	printBytes(&f1, sizeof f1, true);
	printf("sign = 0x%X, exponent = 0x%X, fractional part = 0x%X\n",
		f1.sign, f1.exp, f1.fr);

	/*
	 * 32-bit registers
	*/
	{
		typedef unsigned char BYTE;
		typedef uint16_t WORD;
		typedef uint32_t DWORD;

		typedef union Registers {
			struct {
				DWORD eax, ebx, ecx, edx;
			};
			struct {
				WORD ax, : 16;
				WORD bx, : 16;
				WORD cx, : 16;
				WORD dx, : 16;
			};
			struct {
				BYTE al, ah, : 8, : 8;
				BYTE bl, bh, : 8, : 8;
				BYTE cl, ch, : 8, : 8;
				BYTE dl, dh, : 8, : 8;
			};
		} Registers;

		Registers r = {0};
		r.al = 0x11, r.ah = 0x22;
		r.bl = 0x33, r.bh = 0x44;
		r.cl = 0x55, r.ch = 0x66;
		r.dl = 0x77, r.dh = 0x88;
		r.edx = 0x44332211;

		printBytes(&r, sizeof(r), false);
	}


	// Custom Float
	{
		typedef union MyFloat {
			float value;
			struct {
				unsigned int fr : 23, exp : 8, sign : 1;
			};
		} MyFloat;

		MyFloat f;
		f.fr = 0x0;
		f.exp = 0x80;
		f.sign = 0x1;

		printBytes(&f, sizeof(f), false);
		printf("Resulting float = %g\n", f.value);
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
	return (i << num_shifts) | (i >> (NUM_BITS(i) - num_shifts));
}

/*
 * Shift number i right by num_shifts bits.
 * Shifted bits will move to the left end.
*/
unsigned int
shiftRight(unsigned int i, unsigned char num_shifts)
{
	return (i >> num_shifts) | (i << (NUM_BITS(i) - num_shifts));
}


/*
 * Return num_bits bits starting from the starting_bit bit of i.
*/
unsigned int
selectBits(unsigned int i, uint8_t starting_bit, uint8_t num_bits)
{
	return (i >> (starting_bit + 1 - num_bits)) & ~(~0U << num_bits);
}


// Return number of bits set to 1
uint8_t
countOnes(unsigned int i)
{
	uint8_t n = 0;

	/*
	 * Method 1 - most obvious.
	while (i) {
		n += i & 1;
		i >>= 1;
	}
	*/


	/*
	 * Method 2 - K & R C
	*/
	while (i) {
		i &= i - 1;
		n++;
	}

	return n;
}


/*
 * Return reversed bits of i
*/
unsigned int
reverseBits(unsigned int i)
{
	unsigned int j;
	unsigned char num_bits;

	j = 0U;
	num_bits = sizeof(i) << 3;

	while (num_bits--) {
		j <<= 1;
		j |= i & 1;
		i >>= 1;
	}

	return j;
}
