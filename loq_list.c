#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "loq.h"

#define CLEARBUF for (int i = 0; i < 21; i++) buf[i] = 0;

#define print(str) write(1, (str), strlen((str)))

typedef enum {
	invalid,
	timestamp,
	message
} automaton_state;

void loq_list() {
	// Get filename
	char *filename = getenv("LOQFILE");
	if (filename == NULL) {
		print("Please set the LOQFILE environment variable.\n");
		_exit(2);
	}

	// Open file
	int fd = open(filename, O_RDONLY);
	
	// Title
	print("# Loq\n\n");

	// Read file
	automaton_state s = timestamp;
	char buf[21];
	CLEARBUF
	int i = 0;
	time_t last = 0;
	time_t current = 0;
	struct tm *tm;
	int lastyear = 1970, lastmonth = 0, lastday = 1;
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
						print("## ");
						print(itoa(1900 + tm->tm_year, 10));
						print("-");
						if (tm->tm_mon < 9)
							print("0");
						print(itoa(tm->tm_mon + 1, 10));
						print("-");
						if (tm->tm_mday < 10)
							print("0");
						print(itoa(tm->tm_mday, 10));
						print("\n\n");
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
