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
	c[ptr++] = in;
	if (force || ptr == BUFLEN) {
		write(fd, c, ptr);
		ptr = 0;
	}
}
