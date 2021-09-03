/*
 * For testing purposes and mini examples.
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


#define SIZE 11


// Prints n elements of int array a
static void print_arr(const int *a, int n);
// Prints n elements of double array a
static void print_double_arr(const double *a, int n);
// Return true if array a of size n contains key
static bool search(const int a[], int n, int key);
// Store zeros in int array of size n
static void store_zeros(int a[], int n);
// Returns sum of multiplied array elements
static double inner_product(const double *a, const double *b, int n);
// Returns pointer to the middle element of array a of size n
static int *find_middle(int a[], int n);
// Returns pointer to the largest element of array a of size n
static int *find_largest(int a[], int n);
// Writes two largest elements of array a into specified parameters
static void find_two_largest(
	const int a[], int n,
	int *largest, int *second_largest
);
// Prints the identity matrix
static void print_identity_matrix(int n);
// Dummy function
static void read_temperatures(void);
// Returns the sum of all elements in 2-dim array of size n*m
static int sum_2dim_arr(int n, int m, const int a[][m]);
// Dummy function
static int evaluate_position(int board_sz, const char (*board)[board_sz]);
// String testing statements
static void test_str(void);
// Reads an input line into s. Skip initial whitespaces. Stop on whitespace.
static int readln(char *s, int n);
// Writes extension of file_name into ext
static void get_ext(const char *file_name, char *ext);
// Creates index url from the specified domain name
static char *build_index_url(const char *dn, char *index_url);
// Returns true if filename fn has an extenstion ext
static bool test_ext(const char *fn, const char *ext);
// Removes filename from url
static char *remove_url_filename(char *url);


int main(void)
{
	srand((unsigned) time(NULL));


	{
		puts("\n\n" "Example: Remove filename from url\n" "##########");

		char url[50];

		printf("Enter url: ");
		fgets(url, sizeof url, stdin);
		*(url + strlen(url) - 1) = 0;

		printf("URL without filename: %s\n", remove_url_filename(url));

		return 0;
	}


	{
		puts("\n\n" "Example: Test if filename has a"
			" specified extension\n" "##########");

		char fn[50], ext[30];

		printf("Enter filename: ");
		fgets(fn, sizeof fn, stdin);
		*(fn + strlen(fn) - 1) = 0;

		printf("Enter extension: ");
		fgets(ext, sizeof ext, stdin);
		*(ext + strlen(ext) - 1) = 0;

		if (test_ext(fn, ext))
			printf("%s has extension %s\n", fn, ext);

	}


	{
		puts("\n\n" "Example: build url name\n" "##########");

		char index_url[50], dn[30];
		printf("Enter domain name: ");
		readln(dn, sizeof(dn) - 1);
		*(dn + strlen(dn) - 1) = 0;
		printf("Your url: %s\n", build_index_url(dn, index_url));

	}


	{
		puts("\n\n" "Example: Find find extension of"
			" specified filename\n" "##########");

		char ext[20], file_name[40];

		printf("Enter filename: ");
		fgets(file_name, sizeof file_name, stdin);
		*(file_name + strlen(file_name) - 1) = 0;
	
		get_ext(file_name, ext);

		printf("Extension is: %s\n", ext);

	}


	{
		puts("\n\n" "Example: Read input line\n" "##########");

		char a[20];
		int n = readln(a, sizeof(a) - 1);

		printf("a = %s\nn = %d\n", a, n);
	}


	{
		puts("\n\n" "Example: Find key in array\n" "##########");
		int a[SIZE], *p = a;
		// Initialize with random numbers
		while (p < a + SIZE)
			*p++ = rand() % 10;
		print_arr(a, SIZE);
		printf("Array%s contain key %d\n", search(a, SIZE, 7) ? "" : " does not", 7);
	}


	{
		puts("\n\n" "Example: Store zeros in array\n" "##########");
		int a[SIZE];
		store_zeros(a, SIZE);
		print_arr(a, SIZE);
	}


	{
		puts("\n\n" "Example: Inner product of 2 arrays\n" "##########");
		double d1[SIZE], d2[SIZE], *pd;
		for (pd = d1; pd < d1 + SIZE; pd++)
			*pd = (double) (rand() % 2);
		for (pd = d2; pd < d2 + SIZE; pd++)
			*pd = (double) (rand() % 2);
		print_double_arr(d1, SIZE);
		print_double_arr(d2, SIZE);
		printf("Inner product: %lf\n", inner_product(d1, d2, SIZE));
	}


	{
		puts("\n\n" "Example: Find middle element of array\n" "##########");
		int a[SIZE], *p = a;
		// Initialize with random numbers
		while (p < a + SIZE)
			*p++ = rand() % 10;
		print_arr(a, SIZE);
		printf("Middle element: %d\n", *(find_middle(a, SIZE)));
		printf("Largest element: %d\n", *(find_largest(a, SIZE)));
	}

	
	{
		puts("\n\n" "Example: 2 largest numbers in array\n" "##########");
		int a[SIZE], *p = a;
		// Initialize with random numbers
		while (p < a + SIZE)
			*p++ = rand() % 10;
		print_arr(a, SIZE);
		int first_largest, second_largest;
		find_two_largest(a, SIZE, &first_largest, &second_largest);
		printf("First largest: %d\nSecond largest: %d\n",
				first_largest, second_largest);
	}


	{
		puts("\n\n" "Example: Print identity matrix\n" "##########");
		print_identity_matrix(SIZE);
	}


	{
		puts("\n\n" "Example: Read temperatures\n" "##########");
		read_temperatures();
	}

	
	{
		puts("\n\n" "Example: Sum array elements\n" "##########");
		int a[SIZE], *p = a;
		// Initialize with random numbers
		while (p < a + SIZE)
			*p++ = rand() % 10;
		print_arr(a, SIZE);
		int n, m;
		for (n = 2; SIZE % n != 0; n++)
		m = SIZE / n;
		printf("Sum of array elements: %d\n", sum_2dim_arr(n, m, (const int (*)[m]) a));
	}


	{
		puts("\n\n" "Example: Print random chess board score\n" "##########");
		char board[8][8], *p;
		for (p = *board; p < *board + sizeof(*board) * sizeof(*board); p++) {
			int rnd = rand() % 10;
			switch (rnd) {
				case 1:		*p = 'k'; break;
				case 2:		*p = 'q'; break;
				case 3:		*p = 'r'; break;
				case 4:		*p = 'b'; break;
				case 5:		*p = 'n'; break;
				case 6:		*p = 'p'; break;
				default:	*p = ' ';
			}
			if (rand() % 2)
				*p = toupper(*p);
		}
		printf("Chess board score: %d\n",
			evaluate_position(sizeof(*board), (const char (*)[sizeof(*board)]) board));
	}


	{
		puts("\n\n" "Example: Test string and char* behaviour\n" "##########");
		test_str();
	}


	return 0;
}


void print_arr(const int *a, int n)
{
	printf("Your array:");

	while (n > 0)
		printf(" %d", (n--, *a++));
	printf("\n");
}


void print_double_arr(const double *a, int n)
{
	printf("Your array:");
	for ( ; n > 0; n--, a++)
		printf(" %.2lf", *a);
	printf("\n");
}


bool search(const int a[], int n, int key)
{
	for ( ; n > 0; n--, a++)
		if (*a == key)
			return true;
	return false;
}


void store_zeros(int a[], int n)
{
	for ( ; n > 0; n--, a++)
		*a = 0;
}


double inner_product(const double *a, const double *b, int n)
{
	double product = 0.0;

	for ( ; n > 0; a++, b++, n--)
		product += *a * *b;

	return product;
}


int *find_middle(int a[], int n)
{
	return a + n / 2;
}


int *find_largest(int a[], int n)
{
	int *p_largest;

	for ( p_largest = a; n > 0; a++, n--)
		if (*a > *p_largest)
			p_largest = a;

	return p_largest;
}


void find_two_largest(
	const int a[], int n,
	int *largest, int *second_largest
) {
	for (*largest = *second_largest = *a; n > 0; n--, a++)
		if (*a > *largest)
			*second_largest = *largest, *largest = *a;
		else if (*a > *second_largest)
			*second_largest = *a;
}


void print_identity_matrix(int n)
{
	int matrix[n][n], *p, counter;

	for (p = *matrix, counter = n; p < matrix[n]; p++, counter++)
		if (counter == n)
			counter = -1, *p = 1;
		else
			*p = 0;

	printf("Your identity matrix:\n");
	for (counter = 0, p = *matrix; p < matrix[n]; p++, counter++) {
		if (counter == n) {
			printf("\n");
			counter = 0;
		}
		printf(" %d", *p);
	}

	printf("\n");
}


void read_temperatures(void)
{
	int days = 7, hours = 24, key = 32, temperatures[days][hours];
	int (*p)[hours], *q;

	for (q = *temperatures; q < *(temperatures + days); q++)
		*q = rand() % (key * 2);

	for (p = temperatures; p < temperatures + days; p++) {
		printf("Largest temperature for day %ld is %d\n",
			p - temperatures + 1, *find_largest(*p, hours));
		if (search(*p, hours, key)) {
			printf("Day %ld has temperature %d\n", p - temperatures + 1, key);
			printf("Temperature readings for day %ld:\n", p - temperatures + 1);
			for (q = *p; q < *(p + 1); q++)
				printf(" %d", *q);
			printf("\n");
		}
	}
}


int sum_2dim_arr(int n, int m, const int a[][m])
{
	int sum = 0;
	const int *p;

	for (p = *a; p < a[n]; p++)
		sum += *p;

	return sum;
}


int evaluate_position(int board_sz, const char (*board)[board_sz])
{
	int sum = 0, score;
	const char *p;

	for (p = *board; p < *board + board_sz * board_sz; p++) {
		switch(tolower(*p)) {
			case 'q':	score = 9; break;
			case 'r':	score = 9; break;
			case 'b':	score = 9; break;
			case 'n':	score = 9; break;
			case 'p':	score = 9; break;
			default:	score = 0;
		}

		if (*p == tolower(*p))
			score = -score;

		sum += score;
	}

	return sum;
}


void test_str(void)
{
	{
		// Test char[] and char * behaviour
		char a[] = "abc", *p = a, *q = "def";
		printf("%4.3s\n", q);
		printf("%c\n", p[3] = 'b');
		//printf("%c\n", q[0] = 'e')	Will give seg fault
	}

	{
		// Test strcpy
		char s1[SIZE];
		char s2[SIZE + 1], *q = s2;

		// Initialize s1
		for ( ; q < s2 + SIZE; q++)
			*q = q - s2 + 'a';
		*q = '\0';

		// Safe copy s2 into s1.
		strncpy(s1, s2, sizeof(s1) - 1);
		s1[sizeof(s1) - 1] = '\0';

		// Unsafe fast copy s1 into s2.
		strcpy(s2, s1);
	}

	{
		// Test strcat
		char s1[5] = "defg";
		char s2[8] = "abc";
		char s3[] = "abc";

		// Safe strcat
		strncat(s2, s1, sizeof(s2) - strlen(s2) - 1);

		// Unsafe strcat
		char s4[sizeof("abc") + 3] = "def";
		printf("%s\n", strcat(s4, s3));
	}

	{
		// Test gets and scanf
		char s1[9], *p;

		printf("Enter your string: ");
		fgets(s1, sizeof s1, stdin);
		printf("Your string: ");
		for (p = s1; p < s1 + 9; p++)
			putchar(*p == 0 ? '0' : *p);
		printf("\n");

		printf("Enter your string: ");
		scanf("%3s", s1);
		for (p = s1; p < s1 + 9; p++)
			putchar(*p == 0 ? '0' : *p);
		printf("\n");
	}

	{
		// Test strcmp
		char s1[] = " A";
		char s2[] = " a";
		char s3[3];
		int cmp;

		cmp = strcmp(s1, s2);
		
		if (cmp < 0)
			strcpy(s3, "<");
		else if (cmp == 0)
			strcpy(s3, "==");
		else
			strcpy(s3, ">");

		printf("%s %s %s\n", s1, s3, s2); 
	}
}


int readln(char *s, int n)
{
	char c;
	int i = 0;
	bool skip_whitespace = true;

	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			// Skip leading whitespaces
			if (skip_whitespace)
				continue;
			// Stop reading when whitespace reached
			else
				break;
		}
		skip_whitespace = false;
		if (i <  n)
			s[i++] = c;
	}

	// Store new line if it was last character read.
	if (c == '\n' && i < n)
		s[i++] = c;

	s[i] = '\0';

	return i;
}


void get_ext(const char *file_name, char *ext)
{
	const char *p = file_name;

	// Go to the end of the file name
	while (*p)
		p++;

	// Find the dot
	while (file_name <= p) {
		if (*p == '.')
			break;
		p--;
	}

	// extension was not found
	if (p < file_name) {
		strcpy(ext, "");
		return;
	}

	strncpy(ext, p + 1, strlen(file_name) - (p - file_name));
}


char *build_index_url(const char *dn, char *index_url)
{
	strcpy(index_url, "http://www.");
	strcat(index_url, dn);
	strcat(index_url, "/index.html");
	return index_url;
}


static bool test_ext(const char *fn, const char *ext)
{
	const char *p, *q;

	p = fn + strlen(fn);
	q = ext + strlen(ext);

	for ( ; fn <= p && ext <= q; p--, q--)
		if (toupper(*p) != toupper(*q))
			break;

	if (q < ext && fn <= p && *p == '.')
		return true;
	return false;
}


static char *remove_url_filename(char *url)
{
	char *p;

	for (p = url + strlen(url); url < p; p--)
		if (*p == '/')
			*p = '\0', p = url;

	return url;
}
