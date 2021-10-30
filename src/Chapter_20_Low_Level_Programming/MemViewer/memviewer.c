/*
 * Print the contents of specified memory address.
 *
 * Resembles a Debugger.
*/


#include <stdio.h>
#include <ctype.h>
#include <stddef.h>


#define NON_PRINTABLE_CHAR '.'
#define NUM_BYTES_ON_THE_LINE 8


typedef unsigned char Byte;


// Print contents of memory block of size num_bytes in Hex Format.
void printBytesHex(Byte *start, size_t num_bytes);
// Print contents of memory block of size num_bytes in Char Format.
void printBytes(Byte *start, size_t num_bytes);


int main(void)
{
	Byte *addr;
	size_t num_bytes, remainder;

	printf("Address of main: 0x%zX\n", (size_t) main);
	printf("Address of addr: 0x%zX\n\n", (size_t) &addr);

	printf("Memory Address: ");
	if (!scanf("%lx", (size_t *) &addr))
		return 1;
	printf("Number of Bytes: ");
	if (!scanf("%zu", &num_bytes))
		return 1;;

	printf("\n%16s%4s%24s%4s%8s\n", "Address", "", "Bytes", "", "Chars");
	printf(	"================" "%4s" "========================" "%4s" "========", "", "");

	while (num_bytes >= NUM_BYTES_ON_THE_LINE) {
		printf("\n%16zX", (size_t) addr);
		printf("%4s", "");

		printBytesHex(addr, NUM_BYTES_ON_THE_LINE);
		printf("%4s", "");

		printBytes(addr, NUM_BYTES_ON_THE_LINE);

		num_bytes -= NUM_BYTES_ON_THE_LINE;
		addr += NUM_BYTES_ON_THE_LINE;
	}

	if (!num_bytes) {
		printf("\n");
		return 0;
	}


	printf("\n%16zX", (size_t) addr);
	printf("%4s", "");

	remainder = NUM_BYTES_ON_THE_LINE - num_bytes;
	printBytesHex(addr, num_bytes);
	while (remainder--)
		printf("%3s", "");
	printf("%4s", "");

	remainder = NUM_BYTES_ON_THE_LINE - num_bytes;
	printBytes(addr, num_bytes);
	while (remainder--)
		putchar('.');

	printf("\n");

	return 0;
}


// Print contents of memory block of size num_bytes in Hex Format.
void printBytesHex(register Byte *start, size_t num_bytes)
{
	while (num_bytes--)
		printf("%-3.2X", *start++);
}


// Print contents of memory block of size num_bytes in Char Format.
void printBytes(register Byte *start, size_t num_bytes)
{
	while (num_bytes--) {
		if (isprint(*start))
			putchar(*start);
		else
			putchar(NON_PRINTABLE_CHAR);
		start++;
	}
}
