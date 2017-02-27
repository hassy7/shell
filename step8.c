#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80


void split_cmd(char* cmd, int* ac, char* av[]);
void split_proc(int* ac, char* av[], int *Pac, char* Pav[], int* count);
int countPipe(int ac, char* av[]);
//int countRedi(int Pac, char* Pav[]); 
//int returnRedi(int Pac, char* Pav[], int rednm);
int redin(int Pac, char* Pav[]);
int redout(int Pac, char* Pav[]);


int main(void)
{
	char *av[MAXWORDNUM];
	int ac;

	char *Pav[MAXWORDNUM];
	int Pac;

	int count;//
	int pronum;//process number

	//コマンドの実行のための引数
	int pid;//process id
	int status;//waiting time

	//use redirect
	int redo;
	int rei;
	int i;
	int fd;

	while (1) {
		char cmd[MAXCMDLEN] = {0};

		printf("\x1b[32mmysh $: \x1b[m");
		if (fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}
		//split cmd to command
		split_cmd(cmd, &ac, av);
		pronum = countPipe(ac, av) + 1;
		for (count = 0; count < pronum; count++) {
			//cut command by pipe
			split_proc(&ac, av, &Pac, Pav, &count);

			//implimant process

			if (strcmp(Pav[0], "exit") == 0) {
				exit(-1);
			} else if (strcmp(Pav[0], "cd") == 0) {
				if (Pac == 1) {
					chdir(getenv("HOME"));
				} else {
					chdir(Pav[1]);
				}
			} else {
				//child process
				pid = fork();
				//pidが0より小さいなら
				if (pid < 0) {
					perror("fork");
					exit(-1);
				} else if (pid == 0) {
					for (i = 0; i < Pac; i++) {
						if (strcmp(Pav[i], ">") == 0) {
							Pav[i] = NULL;
							fd = open(Pav[i + 1], O_WRONLY|O_CREAT, 0644);
							close(1);
							dup(fd);
							close(fd);
						} else if (strcmp(Pav[i], "<") == 0) {
							Pav[i] = NULL;
							fd = open(Pav[i + 1], O_RDONLY|O_CREAT, 0644);
							close(0);
							dup(fd);
							close(fd);
						}
					}
					execvp(Pav[0], Pav);
					exit(-1);
				} else {
					//親プロセス
					wait(&status);
				}
			}

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
		} else {
			break;
		}
	}
	Pav[k] = NULL;// insert NULL into the last of commnd
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

int redin(int Pac, char* Pav[]) {
	int i;
	int inputfile = -1;
	for (i = 0; i < Pac; i++) {
		if (strcmp(Pav[i], "<") == 0) {
			inputfile = i;
			break;
		}
	}
	return inputfile;
}

int redout(int Pac, char* Pav[]) {
	int i;
	int count = -1;
	for (i = 0; i < Pac; i++) {
		if (strcmp(Pav[i], ">") == 0) {
			count = i;
			break;
		}
	}
	return count;
}
