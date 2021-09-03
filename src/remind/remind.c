/*
 * Prints a one-month reminder lists
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_REMINDERS 3
#define MSG_STR_LENGTH 60
// Length of month/day <hh:mm> string
#define MDT_STR_LENGTH 12
#define REMINDER_LENGTH (MSG_STR_LENGTH + MDT_STR_LENGTH + 1)

#define TERMINATING_CHAR '\n'


// Reads n characters of input line into a.
// Returns number of characters that were read.
static int readln(char a[], int n);

// Prints n reminders from reminders array
static void print_reminders(char (*reminders)[REMINDER_LENGTH], int n);

// Reads reminder from stdin into string rem. Return false on termination.
// Writes empty string if wrong month or day or time specified
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
	printf("You need to enter series of reminders using a special format:\n");
	printf("\tmonth/day hh:mm reminder\n");
	printf("Example: 1/29 23:30 Go to dance party.\n");
	printf("If you are done entering reminders, enter an empty line\n");
	printf("Maximum number of reminders: %d\n", MAX_REMINDERS);
	printf("Maximum length of reminder: %d\n\n", REMINDER_LENGTH);

	for (num_rems = 0; num_rems < MAX_REMINDERS; num_rems++) {
		printf("month/day hh:mm reminder: ");
		// User entered terminating char
		if (!read_reminder(rem))
			break;
		// User entered wrong month/date <time>
		if (!*rem) {
			printf("Wrong month/date <time> entered!\n");
			num_rems--;
			continue;
		}
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

	printf("\nmm/dd hh:mm Reminder\n");

	for (p = reminders; p < reminders + n; p++)
		printf("%s\n", *p);
}


bool read_reminder(char rem[REMINDER_LENGTH])
{
	char msg[MSG_STR_LENGTH + 1], mdt_str[MDT_STR_LENGTH + 1];
	char c;
	int month, day, hour, minute;


	// Return false if terminating character was read
	if ((c = getchar()) == TERMINATING_CHAR)
		return false;
	ungetc(c, stdin);

	// Read month day and time 
	month = day = hour = minute = 0;
	scanf("%2d/%2d %2d:%2d", &month, &day, &hour, &minute);
	// Write an empty string if the values aren't proper.
	if (
		month < 1 || month > 12 ||
		day < 1 || day > 31 ||
		hour < 1 || hour > 23 ||
		minute < 1 || minute > 59
	) {
		while ((c = getchar()) != '\n')
			;
		strcpy(rem, "");
		return true;
	}

	sprintf(mdt_str, "%2.2d/%2.2d %2d:%2.2d", month, day, hour, minute);

	// Read msg
	readln(msg, MSG_STR_LENGTH - 1);

	// Concantenate mdt_str and msg and copy them into rem
	strcat(strcpy(rem, mdt_str), msg);

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
