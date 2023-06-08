#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Itoa/itoa.h"
#include "loq.h"

#define fdprint(fd, str) write((fd), (str), strlen((str)))

void loq_add(char *msg) {
	// TODO Create file on first write
	time_t now = time(NULL);
	int fd = open("testloq", O_WRONLY | O_APPEND);
	fdprint(fd, itoa(now, 10));
	fdprint(fd, "\t");
	fdprint(fd, msg);
	fdprint(fd, "\n");
	close(fd);
}
