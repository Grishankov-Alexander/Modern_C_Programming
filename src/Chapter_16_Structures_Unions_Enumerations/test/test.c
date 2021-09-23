/*
 * File for outlining concepts from the chapter.
*/


#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Very nice macro statement.
 * Prints binary representation of an object passed as an argument */
#define PRINT_BINARY(obj) \
	for (int i = sizeof(obj) * 8 - 1; i >= 0; i--) { \
		printf("%d", (obj) >> i & 1); \
		if (i % 8 == 0) printf("\x20"); \
	} printf("\xA")
/* Converts literal value to type */
#define VAL_TO_TYPE(val, type) \
	*(type *) (__typeof__(val)[]) { val, }
/* Prints memory dump of an object */
#define PRINT_MEM(obj) \
	printf(#obj " dump:"); \
	for (char *p = (char *) &(obj); p < (char *) &(obj) + sizeof (obj); p++) { \
		printf("%3.2x", *p & 0xff); \
	} \
	printf("\n")
#define INT64_TO_DOUBLE(i64) *((double *) &(i64)) 
#define PRINT_TOPIC(...) printf("\n\n" #__VA_ARGS__ "\n----------\n")
#define SIZE 30


struct part {
	char *name;
	int number;
	int quantity;
};


struct part create_part(char *name, int number, int quantity);
void print_part(const struct part * const p);


int main(void)
{
	// Structures
	{
		PRINT_TOPIC(structures);


		/*
		 * Declaring and defining
		*/

		// Declaring variable of type struct {...}
		// P.S. types of unnamed structures are incompatible,
		// even if members are the same.
		struct {
			int part_n;
			char *name;
			int in_hand;
		} part1;
		part1.part_n = 13, part1.part_n -= 1;

		// Declare variable of type struct item.
		// item - is a structure tag.
		// struct item can be used later to declare variables
		// of same structure type.
		struct item {
			int part_n;
			char *name;
			int in_hand;
		} part2;
		part2.in_hand = 19, part2.part_n = part2.in_hand; 

		struct item hdd = {228, "Hard Disk Drive", 13};
		/* C99 Feature */
		struct item ssd = {.part_n = 229, "Solid State Drive", .in_hand = 9};
		struct item videocard = {.part_n = 230, .in_hand = 1 };
		printf("Total in_hand: %d\n",
			hdd.in_hand + ssd.in_hand + videocard.in_hand);

		// Same as struct item
		typedef struct item item;
		item dummy1 = {0};
		item dummy2 = {0};

		// Accessing a member and assignments
		dummy1.part_n = videocard.part_n + 1;
		dummy1.name = "dummy part 1";
		dummy1.in_hand = 666;

		// The assignment can be used for copying member arrays
		dummy2 = dummy1;
		printf("dummy2.name = %s\n", dummy2.name);

		// Let us clarify that array copying can succeed
		struct { int arr[SIZE]; } a1 = {{[0] = 1, 2, 3}}, a2;
		a2 = a1;
		a2.arr[0] = 4;
		for (int i = 0; i < 3; i++) {
			printf("a1.arr[%d] = %d\t", i, a1.arr[i]);
			printf("a2.arr[%d] = %d\t", i, a2.arr[i]);
		} printf("\n");
	}


	// Structures and functions
	{
		PRINT_TOPIC(Structures and Functions);

		struct part hdd = create_part("Hard Disk Drive", 9192, 29);
		print_part(&hdd);
	}


	// Nested structures
	{
		PRINT_TOPIC(Nested structures);

		struct name_data {
			const char *first_name;
			const char *last_name;
		};

		struct metrics {
			int id;
			int age;
			int height;
		};

		struct student {
			struct name_data name;
			struct metrics measures;
			const struct student *class_mates;
		};

		/* I did something terrible :) But it works */
		struct student sam_tally = {
			.name = {.first_name = "Samuel", .last_name = "Tally"},
			.measures = {.id = 777, .age = 170, .height = 184},
			.class_mates = (const struct student[]) {
				{.name = {"Jon", "Snow"}},
				{.name = {"Arya", "Stark"}}
			}
		};

		sam_tally.name.first_name = "Sam";

		printf("First name: %s\nLast name: %s\n",
			sam_tally.name.first_name, sam_tally.name.last_name);
	}


	// Array of structures
	{
		PRINT_TOPIC(Array of structures);

		struct part {
			int number;
			char name[SIZE];
			int on_hand;
		};

#		define PRINT_PART(part) \
			printf("struct part " #part " {\n" \
				"\tnumber = %d\n" "\tname = %s\n" "\ton_hand = %d\n" \
				"}\n", (part).number, (part).name, (part).on_hand)

		struct part inventory[SIZE] = {
			{1, "HDD", 30}, {2, "SSD", 30},
			[2].number = 3, [2].name[0] = '\0', [2].on_hand = 0
		};

		strcpy(inventory[2].name, "CPU");
		inventory[2].on_hand = 30;
		PRINT_PART(inventory[2]);
	}


	// Unions
	{
		PRINT_TOPIC(Unions);

		union {
			int a;
			double b;
		} u1 = {.a = 0xffffffff};

		printf("sizeof u1: %zu\n", sizeof u1);
		PRINT_MEM(u1);
		printf("u1.a = %d\n", u1.a);
		printf("u1.b = %lg\n", u1.b);
		u1.a = 0xff;
		PRINT_MEM(u1);
		printf("u1.a = %d\n", u1.a);
		printf("u1.b = %lg\n", u1.b);

		union {
			struct {
				int a;
				int b;
			};

			double d;
		} u2 = { {0xa, 0xb} };

		printf("\nsizeof u2: %zu\n", sizeof u2);
		PRINT_MEM(u2);
		u2.d = 9.99;
		PRINT_MEM(u2);

		struct {
			union {
				char a;
				int b;
			};
		} u3 = {.a = 0x65};

		printf("\nsizeof u3: %zu\n", sizeof u3);
		PRINT_MEM(u3);
		u3.b = 0xabcd;
		PRINT_MEM(u3);

		struct {
			union {
				struct {
					int x;
					double y;
				};

				int ia[4];
			};
		} u4 = {{{0x80000000, 3.14159265}}};
		printf("\nsizeof u4: %zu\n", sizeof u4);
		PRINT_MEM(u4);
		u4.ia[1] = -1;
		int64_t i = 0xabcd;
		u4.y = INT64_TO_DOUBLE(i);
		PRINT_MEM(u4);

		/*
		 * Mixed data structures and union tag fields
		*/
#		define INT_KIND 0
#		define DOUBLE_KIND 1
		union Number {
			int i;
			double d;
		};

		typedef struct {
			int kind;
			union Number u;
		} Number;


		printf("\nSizeof Number: %zu\n", sizeof(Number));
		Number numbers[SIZE] = {
			{INT_KIND, .u.i = 0x1234},
			{INT_KIND, .u.i = 0xffffffff}
		};
		PRINT_MEM(numbers[0]);
		PRINT_MEM(numbers[1]);
		uint64_t tmp = 0x0123456789abcdef;
		numbers[1] = (Number) {DOUBLE_KIND, .u.d = INT64_TO_DOUBLE(tmp)};
		PRINT_MEM(numbers[1]);

		/*
		 * Using unions to save space
		*/
#		define BOOK_KIND 0x0U
#		define SHIRT_KIND 0x1U
		struct catalog_item {
			uint32_t id;
			uint32_t kind;
			double price;
			union {
				struct {
					char name[SIZE];
					int num_pages;
				} book;
				struct {
					char brand[SIZE];
					int size;
				} shirt;
			} item;
		} book1 = {
			0x1U,
			BOOK_KIND,
			INT64_TO_DOUBLE(tmp),
			.item.book.name = "Song of Ice and Fire",
			.item.book.num_pages = 399
		};

		printf("\nSizeof book1: %zu\n", sizeof book1);
		printf("Sizeof book1.item: %zu\n", sizeof book1.item);
		PRINT_MEM(book1);
	}


	// Enumerations
	{
		PRINT_TOPIC(Enumerations);

		// enum without a tag
		{
			enum {CLUBS, DIAMONDS, HEARTS, SPADES} s1;

			s1 = CLUBS;
		}

		// enum with a tag and typedef
		{
			typedef enum suit {CLUBS, DIAMONDS, HEARTS, SPADES} Suit;
			typedef enum {FALSE, TRUE} Bool;

			Bool b = TRUE;
			Suit s1 = HEARTS;
			enum suit s2 = DIAMONDS;
		}

		// Enums as integers 
		{
			int i;
			enum mixed_numbers {
				ZERO,
				TWENTY_FIVE = 25,
				TWENTY_SIX,
				TEN = 10,
				FIVE = 5
			} number;

			i = FIVE;
			number = 10;
			number = TWENTY_SIX;
		}

		// Enums as tag fields
		{
#			undef INT_KIND
#			undef DOUBLE_KIND
			struct number {
				enum {INT_KIND, DOUBLE_KIND} kind;
				union {
					int i;
					double d;
				} u;
			} n = {DOUBLE_KIND, .u.d = 3.14262869e+17};

			PRINT_MEM(n);
		}

		// Enum flags
		{
			PRINT_TOPIC(Enum Flags);

			enum flags {
				READ = 1, WRITE = 1 << 1, APPEND = 1 << 2,
			};

			printf("flags = ");
			PRINT_BINARY(READ | WRITE | APPEND);
		}


		// Struct paddings
		{
			PRINT_TOPIC(Struct paddings);

			struct {
				double d; // 8 bytes
				union {
					double d;
					int i;
					char str[9];
				} u; // 9 bytes + 7 bytes padding
				char str[3]; // 3 bytes + 5 bytes padding
			} s = {0};

			//s.d = VAL_TO_TYPE(0x0123456789abcdef, double);
			strcpy(s.u.str, "abcdefgh");
			strcpy(s.str, "\xa" "\xb");

			printf("sizeof s = %zu\n", sizeof s);
			printf("sizeof s.u = %zu\n", sizeof s.u);
			PRINT_MEM(s);
		}

		{
			union {
				int i;
				struct sss {
					int i_a[5]; // 20 + 4
					double d; // 8
					char str[4]; // 4 + 4
				} s; // 20 bytes + 4 bytes padding
				char str[4];
			} u = {0};

			u.s = (struct sss) {
				{-1, -1, -1, -1, -1},
				VAL_TO_TYPE(0x0123456789abcdef, double),
				"abc",
			};

			printf("sizeof u = %zu\n", sizeof u);
			printf("sizeof u.s = %zu\n", sizeof u.s);
			PRINT_MEM(u);
		}

		{
			struct point {
				int x, y;
			};

			struct shape {
				enum kind {CIRCLE, RECTANGLE,} kind; // 4 bytes
				struct point center; // 8 bytes
				union {
					struct {
						int width, height;
					} rectangle;
					struct {
						int radius;
					} circle;
				} u; // 8 bytes
			} s; 

			s = (struct shape) {
				.kind = RECTANGLE,
				.center = {.x = 0x01234567, .y = 0x89abcdef},
				.u.rectangle = {0x89abcdef, 0x01234567},
			};
			s.kind = CIRCLE;
			s.u.rectangle.height = 25;
			s.u.circle.radius = 5;

			// Wow we can access enum tag outside the scope
			enum kind k;

			printf("sizeof s = %zu\n", sizeof s);
			printf("sizeof s.u = %zu\n", sizeof s.u);
			PRINT_MEM(s);
		}

		// Chessboard
		{
			PRINT_TOPIC(Chessboard);

			typedef enum {
				EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
			} Piece;

			typedef enum {BLACK, WHITE} Color;

			typedef struct {
				Piece p;
				Color c;
			} Square;

			Square board[8][8] = {
				[0] = {{ROOK}, {KNIGHT}, {BISHOP}, {QUEEN},
					{KING}, {BISHOP}, {KNIGHT}, {ROOK}},
				[1] = {{PAWN}, {PAWN}, {PAWN}, {PAWN},
					{PAWN}, {PAWN}, {PAWN}, {PAWN}},
				[6] = {{PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE},
					{PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}, {PAWN, WHITE}},
				[7] = {{ROOK, WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},
					{KING, WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK, WHITE}},
			};
		}
	}


	return 0;
}





struct part create_part(char *name, int number, int quantity)
{
	return (struct part) {.name = name, .number = number, .quantity = quantity};
}


void print_part(const struct part * const p)
{
	printf("struct part {\n"
		"\tname: %s\n"
		"\tnumber: %d\n"
		"\tquantity: %d\n"
		"}\n", p->name, p->number, p->quantity);
}
