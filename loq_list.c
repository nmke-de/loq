#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "loq.h"

#define CLEARBUF for (int i = 0; i < 21; i++) buf[i] = 0;

typedef enum {
	invalid,
	timestamp,
	message
} automaton_state;

void loq_list() {
	// TODO implement
	// Open file
	int fd = open("testloq", O_RDONLY);
	
	// Read file
	automaton_state s = timestamp;
	char buf[21];
	CLEARBUF
	int i = 0;
	time_t last = 0;
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
					last = atol(buf);
					CLEARBUF
					i = 0;
					s = message;
					// TODO Title for day
					break;
				default:
					s = invalid;
					continue;
			}
		else if (s == message)
			switch (c) {
				case '\n':
					printb(1, c, true);
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
