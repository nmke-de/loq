#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "loq.h"

#define fdprint(fd, str) write((fd), (str), strlen((str)))

void loq_add(char *msg) {
	// Fetch current time.
	time_t now = time(NULL);

	// Get filename
	char *filename = getenv("LOQFILE");
	if (filename == NULL) {
		fdprint(1, "Please set the LOQFILE environment variable.\n");
		_exit(2);
	}

	// Open file. Create if it doesn't exist.
	int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);

	// Write message to file.
	fdprint(fd, itoa(now, 10));
	fdprint(fd, "\t");
	fdprint(fd, msg);
	fdprint(fd, "\n");

	// Close file.
	close(fd);
}
