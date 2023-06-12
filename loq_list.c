#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "print/print.h"
#include "loq.h"

// Initialize buffer with zeros.
#define CLEARBUF for (int i = 0; i < 21; i++) buf[i] = 0;

// Needed for parsing
typedef enum {
	invalid,
	timestamp,
	message
} automaton_state;

/*
This procedure prints the log from LOQFILE to the screen, nicely formatted as Markdown.
*/
void loq_list() {
	// Get filename
	char *filename = getenv("LOQFILE");
	if (filename == NULL) {
		log("Please set the LOQFILE environment variable.\n");
		_exit(2);
	}

	// Open file
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		logln("Error when opening file '", filename, "'.");
		_exit(3);
	}
	
	// Title
	char *title = getenv("LOQTITLE");
	if (title == NULL)
		print("# Loq\n\n");
	else
		println("# ", title, "\n");

	// Read file
	automaton_state s = timestamp;
	char buf[21];
	CLEARBUF
	int i = 0;
	time_t last = 0;
	time_t current = 0;
	struct tm *tm;
	int lastyear = 1970, lastmonth = 0, lastday = 1;
	char cyear[5], cmonth[3], cday[3];
	for (char c = readc(fd); c != -1; c = readc(fd)) {
		if (s == timestamp)
			switch (c) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					buf[i++] = c;
					break;
				case '\t':
					last = current;
					current = atol(buf);
					CLEARBUF
					i = 0;
					s = message;
					tm = localtime(&current);
					if (tm->tm_year != lastyear || tm->tm_mon != lastmonth || tm->tm_mday != lastday) {
						lastyear = tm->tm_year;
						lastmonth = tm->tm_mon;
						lastday = tm->tm_mday;
						strncpy(cyear, itoa(1900 + tm->tm_year, 10), 5);
						strncpy(cmonth, itoa(tm->tm_mon + 1, 10), 3);
						if (tm->tm_mon < 9) {
							cmonth[2] = cmonth[1];
							cmonth[1] = cmonth[0];
							cmonth[0] = '0';
						}
						strncpy(cday, itoa(tm->tm_mday, 10), 3);
						if (tm->tm_mday < 10) {
							cday[2] = cday[1];
							cday[1] = cday[0];
							cday[0] = '0';
						}
						println("## ", cyear, "-", cmonth, "-", cday, "\n");
					}
					break;
				default:
					s = invalid;
					continue;
			}
		else if (s == message)
			switch (c) {
				case '\n':
					printb(1, c, true);
					print("\n");
					s = timestamp;
					break;
				case '\0':
					printb(1, c, true);
					s = invalid;
					break;
				default:
					printb(1, c, false);
			}
		else
			break;
	}

	// Close file
	close(fd);

	// Exit if invalid.
	if (s == invalid)
		_exit(1);
}
