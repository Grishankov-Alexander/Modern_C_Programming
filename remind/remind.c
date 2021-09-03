/*
 * Prints a one-month reminder lists
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_REMINDERS 10
#define MSG_STR_LENGTH 60
#define DAY_STR_LENGTH 2
#define REMINDER_LENGTH (MSG_STR_LENGTH + DAY_STR_LENGTH + 1)

#define TERMINATING_CHAR '0'


// Reads n characters of input line into a.
// Returns number of characters that were read.
static int readln(char a[], int n);

// Prints n reminders from reminders array
static void print_reminders(char (*reminders)[REMINDER_LENGTH], int n);

// Reads reminder from stdin into string rem. Return false on termination.
static bool read_reminder(char rem[REMINDER_LENGTH]);

// Writes reminder rem into reminders array of length num_rem.
static void write_reminder(
	char rem[REMINDER_LENGTH],
	char (*reminders)[REMINDER_LENGTH],
	int num_rem
);


int main(void)
{
	char reminders[MAX_REMINDERS][REMINDER_LENGTH];
	char rem[REMINDER_LENGTH];
	int num_rems;

	printf("\nThis program prints a list of daily reminders\n");
	printf("You need to enter series of reminders using a format"
		" <day reminder>. As an example:\n");
	printf("12 Susan's Birthday\n");
	printf("If you are done entering reminders, enter '%c'\n",
		TERMINATING_CHAR);
	printf("Maximum number of reminders: %d\n", MAX_REMINDERS);
	printf("Maximum length of reminder: %d\n\n", REMINDER_LENGTH);

	for (num_rems = 0; num_rems < MAX_REMINDERS; num_rems++) {
		printf("Enter <day reminder>: ");
		// User entered terminating char
		if (!read_reminder(rem))
			break;
		write_reminder(rem, reminders, num_rems);
	}

	print_reminders(reminders, num_rems);

	return 0;
}



int readln(char a[], int n)
{
	char c, *p = a;

	while ((c = getchar()) != '\n') {
		if (n > 0)
			*p++ = c, n--;
	}
	
	*p = '\0';

	return p - a;
}


void print_reminders(char (*reminders)[REMINDER_LENGTH], int n)
{
	char (*p)[REMINDER_LENGTH];

	printf("\nDay Reminder\n");

	for (p = reminders; p < reminders + n; p++)
		printf(" %s\n", *p);
}


bool read_reminder(char rem[REMINDER_LENGTH])
{
	char msg[MSG_STR_LENGTH + 1], day_str[DAY_STR_LENGTH + 1];
	char c;
	int day;

	// Return false if terminating character was read
	if ((c = getchar()) == TERMINATING_CHAR)
		return false;
	ungetc(c, stdin);

	// Read d-digit day
	scanf("%2d", &day);
	// Return
	sprintf(day_str, "%2d", day);

	// Read msg
	readln(msg, MSG_STR_LENGTH);

	// Concantenate day_str and msg and copy them into rem
	strcat(strcpy(rem, day_str), msg);

	return true;
}


void write_reminder(
	char rem[REMINDER_LENGTH],
	char (*reminders)[REMINDER_LENGTH],
	int num_rem
) {
	char (*p)[REMINDER_LENGTH], (*q)[REMINDER_LENGTH];

	// Find placement for rem
	for (p = reminders; p < reminders + num_rem; p++)
		if (strcmp(rem, *p) < 0)
			break;
	
	// Move other reminders up
	for (q = reminders + num_rem; p < q; q--)
		strcpy(*q, *(q - 1));

	// Write reminder
	strcpy(*p, rem);
}
