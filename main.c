#include <string.h>
#include <alloca.h>
#include "loq.h"

// Loq = Log quickly

int main(int argc, char **argv) {
	if (argc == 1)
		loq_list();
	else {
		// Parse arguments to message, with each argument separated by space.
		// Allocate memory
		int len = argc - 1;
		int *lens = alloca(sizeof(int) * (argc - 1));
		for (int i = 1; i < argc; i++) {
			lens[i - 1] = strlen(argv[i]);
			len += lens[i - 1];
		}
		char *msg = alloca(sizeof(char) * len);
		// Copy arguments to msg
		for (int i = 1, l = 0; i < argc; i++) {
			strncpy(msg + l, argv[i], lens[i - 1]);
			l += lens[i - 1];
			msg[l++] = ' ';
		}
		msg[len - 1] = '\0';
		loq_add(msg);
	}
	return 0;
}
