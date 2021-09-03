/*
 * Program to find the closest departure time
 * for the time entered by the user
*/


#include <stdio.h>
#include <ctype.h>


#define NUM_ELEMENTS(x) ((int) (sizeof(x) / sizeof((x)[0])))


// Array of departure times (number of minutes since midnight)
static int departures[] = {
	(8 * 60),
	(9 * 60 + 43),
	(11 * 60 + 19),
	(12 * 60 + 47),
	(14 * 60),
	(15 * 60 + 45),
	(19 * 60),
	(21 * 60 + 45)
};
// Array of arrival times for each departure
static int arrivals[NUM_ELEMENTS(departures)] = {
	(10 * 60 + 16),
	(11 * 60 + 52),
	(13 * 60 + 31),
	(15 * 60),
	(16 * 60 + 8),
	(17 * 60 + 55),
	(21 * 60 + 20),
	(23 * 60 + 58)
};


// Asks for time in 12-hour format. Returns minutes since midnight.
static int ask_time(void);
// Finds closest flight.
// Writes its departure and arrival to *departure and *arrival
static void find_closest_flight(
	int min_since_midn,
	int *departure, int *arrival
);


int main(void)
{
	int time, departure, arrival;

	time = ask_time();

	find_closest_flight(time, &departure, &arrival);

	printf("Closest departure: %.2d:%.2d\n", departure / 60, departure % 60);
	printf("Arrives at %.2d:%.2d\n", arrival / 60, arrival % 60);

	return 0;
}


static int ask_time(void)
{
	int h, m;
	char s;

	printf("Enter time: (hh:mm<AM|PM>) ");
	scanf("%d :%d %cM", &h, &m, &s);

	if (h < 0 || h > 12 || m < 0 || m > 59)
		return 0;

	if (h == 12) h = 0;
	switch(tolower(s)) {
		case 'a': return h * 60 + m;
		case 'p': return (h + 12) * 60 + m;
		default: return 0;	
	}
}


static void find_closest_flight(
	int time,
	int *departure, int *arrival
) {
	int i;

	// Find index of departure that goes after time
	for (i = 0; i < NUM_ELEMENTS(departures); i++)
		if (departures[i] > time)
			break;

	// Find closest departure
	if (i == NUM_ELEMENTS(departures))
		i--;
	else if (i > 0)
		if (time - departures[i - 1] < departures[i] - time)
			i--;

	*departure = departures[i];
	*arrival = arrivals[i];
}
