/*
 * One-month reminder list
 * sorted by day and time.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define SZ_ADDEND 5 /* For reallocation */
#define MSG_LENGTH 50 /* max characters in message */


static int num_reminders = 0;
static int max_reminders = 0;

static struct reminder {
	int day; // 1 - 31
	int time; // in seconds
	char *msg; // reminder
} *reminders = NULL;


/* Allocates/Reallocates space for reminders. Returns NULL on failure */
struct reminder *allocate_space(struct reminder *prev);

/* Free space allocated for reminders. Clear counter. Reset *p */
void clean_reminders(void);

/* Reads a day from stdin. Returns -1 on failure */
int read_day(void);

/* Read time from stdin.
 * Returns time in seconds.
 * Returns -1 on failure 
*/
int read_time(void);

/*
 * Read n - 1 characters into string. Return number of characters read.
*/
int read_msg(char *str, int n);

// Print reminders
void print_reminders(void);


int main(void)
{
	int day, time;
	char msg[MSG_LENGTH + 1]; // To store message temporarily
	char *m; // For Allocating and storing message in reminder
	char c; // To check for exit char
	struct reminder r; // For construction of a new reminder
	struct reminder *p, *q; // For indexing into reminders array
	struct reminder *new_storage; // For increasing storage of reminders (realloc)


	for ( ; ; ) {

		// Check for storage
		if (num_reminders == max_reminders) {
			new_storage = allocate_space(reminders);
			if (new_storage) {
				reminders = new_storage;
				new_storage = NULL;
			} else {
				printf("Allocation error. Free your memory!\n");
				printf("0 - Exit\n1 - Try again\nEnter the command: ");
				int command = 1;
				scanf("%d", &command);
				switch (command) {
					case 0:
						print_reminders();
						clean_reminders();
						exit(EXIT_SUCCESS);
				}
				continue;
			}
		}

PROMPT_REMINDER:
		// Prompt for reminder
		printf("\nReminder format: day hh:mm message\n");
		printf("Enter Empty reminder to exit\n");
		printf("Enter 'p' to print reminders\n");
		printf("Enter reminder: ");

		// Check for exit
		c = getchar();
		switch (c) {
			case '\xa':
				print_reminders();
				clean_reminders();
				exit(EXIT_SUCCESS);
			case 'p':
				print_reminders();
				while ((c = getchar()) != '\xa')
					;
				goto PROMPT_REMINDER;
			default:
				ungetc(c, stdin);
				break;
		}

		// Read day, time and reminder message
		day = read_day();
		time = read_time();
		read_msg(msg, sizeof msg);

		// Verify msg, day and time
		if (day == -1 || time == -1) {
			printf("Error: wrong reminder format!\n");
			continue;
		}

		// Allocate space for message. Verify allocation.
		m = malloc(strlen(msg) + 1);
		if (!m) {
			printf("Allocation error. Free your memory!\n");
			continue;
		}
		strcpy(m, msg);

		// Construct reminder
		r.day = day;
		r.time = time;
		r.msg = m;

		// Find a placement for the new reminder
		// based on date and time
		for (p = reminders; p < reminders + num_reminders; p++) {
			if (day > p->day)
				continue; 
			else if (day < p->day)
				break;
			else if (time >= p->time)
				continue;
			else
				break;
		}

		// Move old reminders up one spot if necessary
		for (q = reminders + num_reminders; q > p; q--)
			*q = *(q - 1);

		// Write new reminder into array
		*p = r;

		// increase counter
		num_reminders++;
	}

	return 0;
}


/* Allocates/Reallocates space for reminders. Returns NULL on failure */
struct reminder *allocate_space(struct reminder *prev)
{
	struct reminder *next;

	next = realloc(prev, sizeof(*next) * (num_reminders + SZ_ADDEND));
	if (!next)
		return NULL;
	max_reminders += SZ_ADDEND;
	return next;
}


/* Free space allocated for reminders. Clear counter. Reset *p */
void clean_reminders(void)
{
	struct reminder *p;

	// First deallocate messages in reminders
	for (p = reminders; p < reminders + num_reminders; p++)
		free(p->msg);

	free(reminders);
	reminders = NULL;
	num_reminders = 0;
	max_reminders = 0;
}


/* Reads a day from stdin. Returns -1 on failure */
int read_day(void)
{
	int day = 0;

	scanf("%2d", &day);
	if (day < 1 || 31 < day)
		day = -1;

	return day;
}

/* Read time from stdin. Format: hh:mm
 * Returns time in seconds.
 * Returns -1 on failure 
*/
int read_time(void)
{
	int h, m;

	if (scanf("%d :%d", &h, &m) != 2)
		return -1;

	if (h < 0 || 23 < h || m < 0 || 59 < m)
		return -1;

	while (h-- > 0)
		m += 60;

	return m * 60;
}

/*
 * Skip initial whitespaces
 * Read n - 1 characters into string until newline of EOF.
 * Return number of characters read.
*/
int read_msg(char *str, int n)
{
	char c, *p = str;

	while (isspace(c = getchar()))
		;
	while (c != EOF && c != '\xa') {
		if (p < str + n - 1)
			*p++ = c;
		c = getchar();
	}

	*p = 0;

	return p - str;
}


void print_reminders(void)
{
	struct reminder *p;
	int h, m;

	printf("\n\nOne-month reminder list\n==========\n");

	for (p = reminders; p < reminders + num_reminders; p++) {
		h = p->time / 3600;
		m = p->time % 3600 / 60;
		printf("%.2d %.2d:%.2d %s\n", p->day, h, m, p->msg);
	}
}
