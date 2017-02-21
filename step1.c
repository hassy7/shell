#include <stdio.h>
#include <stdlib.h>
#define MAX 256

int main (void) {
	do {
		char cmd[MAX + 1] = {0};
		fprintf(stdout, "mysh $");
		if (fgets(cmd, MAX + 1, stdin) == NULL) {
			fprintf (stderr, "input error");
		}
		fprintf(stdout, "%s", cmd);
	} while (1);
	return 0;
}
