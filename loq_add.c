#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "loq.h"

#define fdprint(fd, str) write((fd), (str), strlen((str)))

void loq_add(char *msg) {
	// Fetch current time.
	time_t now = time(NULL);

	// Open file. Create if it doesn't exist.
	int fd = open("testloq", O_CREAT | O_WRONLY | O_APPEND, 0644);

	// Write message to file.
	fdprint(fd, itoa(now, 10));
	fdprint(fd, "\t");
	fdprint(fd, msg);
	fdprint(fd, "\n");

	// Close file.
	close(fd);
}
