#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80


void split_cmd(char* cmd, int* ac, char* av[]);
void print_arg(char* arg);
void print_args(int ac, char** av);
void split_proc(int* ac, char* av[], int *Pac, char* Pav[], int* count);
int countPipe(int ac, char* av[]);


int main(void)
{
	char *av[MAXWORDNUM];
	int ac;

	char *Pav[MAXWORDNUM];
	int Pac;

	int i = 0;
	int count = 0;

	while (1) {
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if (fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}

		split_cmd(cmd, &ac, av);
		printf("Total Process = %i\n", countPipe(ac, av) + 1);
		while (count < (countPipe(ac, av) + 1)) {
			split_proc(&ac, av, &Pac, Pav, &count);
			printf("Proc %i\nPac = %i\n", count + 1, Pac);
			while (i < Pac) {
				printf("Pav[%i] = %s\n", i, av[i]);
				i++;
			}
			printf("\n");
			i = 0;
			count++;
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

void print_arg(char* arg);
void print_args(int ac, char** av) {
	int i = 0;
	while (i < ac) {
		printf("av[%i]: %s\n", i, av[i]);
		i++;
	}
}

void split_proc(int* ac, char* av[], int *Pac, char* Pav[], int* count) {
	int i = 0;
	int j = 0;
	int k = 0;//Pavに格納
	while (i < *count) {
		while (*av[j] != '|') {
			j++;
		}
		j++;
		i++;
	}
	while (*av[j] != '|') { 
		*Pav[k] = *av[j];
		k++;
		j++;
	}
	*Pac = k;
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
