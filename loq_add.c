#include <unistd.h>
#include <string.h>
#include "loq.h"

void loq_add(char *msg) {
	write(1, msg, strlen(msg));
	// TODO implement
}
