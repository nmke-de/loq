#include <unistd.h>
#include <string.h>
#include "loq.h"

#define BUFLEN 512

/*
put characters into a buffer and then print to fd
*/
void printb(int fd, char in, bool force) {
	static char c[BUFLEN];
	static int ptr = 0;
	// Only append buffer if meaningful character was provided.
	if (in != -1)
		c[ptr++] = in;
	if (force || ptr == BUFLEN) {
		write(fd, c, ptr);
		ptr = 0;
	}
}
