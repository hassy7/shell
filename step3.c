#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80


void split_cmd(char* cmd, int* ac, char* av[]);
void split_proc(int* ac, char* av[], int *Pac, char* Pav[], int* count);
int countPipe(int ac, char* av[]);


int main(void)
{
	char *av[MAXWORDNUM];
	int ac;

	char *Pav[MAXWORDNUM];
	int Pac;

	int i;
	int count;
	int pronum;

	while (1) {
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if (fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}

		split_cmd(cmd, &ac, av);
		pronum = countPipe(ac, av) + 1;
		for (count = 0; count < pronum; count++) {
			split_proc(&ac, av, &Pac, Pav, &count);
			printf("Proc %i\nPac = %i\n", count, Pac);
			for (i = 0; i < Pac; i++) {
				printf("Pav[%i] = %s\n", i, Pav[i]);
			}
			printf("\n");
		}
	}
}

void split_cmd(char* cmd, int* ac, char* av[]) {
	int i = 0;
	*ac = 0;
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

void split_proc(int* ac, char* av[], int *Pac, char* Pav[], int* count) {
	int i = 0;
	int j = 0;
	int k;
	*Pac = 0;

	while (i < *count) {
		while (*av[j] != '|') {
			j++;
		}
		j++;
		i++;
	}

	for (k = 0; j < *ac; j++, k++) {
		if (*av[j] != '|') { 
			Pav[k] = av[j];
			*Pac = *Pac + 1;
		} else break;
	}
}

int countPipe(int ac, char* av[]) {
	// パイプの数を数える
	int i = 0;
	int count = 0;
	while (i < ac) {
		if (*av[i] == '|') count++;
		i++;
	}
	return count;
}
