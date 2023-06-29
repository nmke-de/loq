#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "print/print.h"
#include "loq.h"

/*
This procedure takes a message msg and writes it, together with a timestamp, to the LOQFILE.
*/
void loq_add(char *msg) {
	// Fetch current time.
	time_t now = time(NULL);

	// Get filename
	char *filename = getenv("LOQFILE");
	if (filename == NULL) {
		log("Please set the LOQFILE environment variable.\n");
		_exit(2);
	}

	// Open file. Create if it doesn't exist.
	int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);

	// Write message to file.
	fdprintv(fd, cargs(itoa(now, 10), "\t", msg, "\n"));

	// Close file.
	close(fd);
}
