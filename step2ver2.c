#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);
void print_arg(char* arg);
void print_args(int ac, char** av);


int main(void)
{
	char *av[MAXWORDNUM];
	int ac;

	while(1) {
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}

		split_cmd(cmd, &ac, av);

		print_args(ac, av);
	}
}

void split_cmd(char* cmd, int* ac, char* av[]) {
	int i = 0;
	*ac = 0;

	//もしパイプがあったら
	while (1) {
		if (cmd[i] == '\0') break;
		if (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n') {
			cmd[i] = '\0';
		} else {
			if (cmd[i - 1] == '\0' || i == 0) {
				av[*ac] = &cmd[i];
				*ac = *ac + 1;
			}
		}
		i++;
	}
	
}

void print_arg(char* arg);
void print_args(int ac, char** av) {
	int i = 0;
	while (i < ac) {
		printf("av[%i]: %s\n", i, av[i]);
		i++;
	}
}

