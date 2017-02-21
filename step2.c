#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);


void print_arg(char* arg);
void print_args(int ac, char** av);


int main(void)
{ char *av[MAXWORDNUM];
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
	//コマンドを空白で切る
	int i = 0;
	char* token;
	token = strtok(cmd, " |><&\t\n");
	while (token != NULL){
		av[i] = token;
		token = strtok(NULL, " |><&\t\n");
		i++;
	}
	*ac = i;
}
void print_arg(char* arg);
void print_args(int ac, char** av) {
	int i = 0;
	printf("%d\n", ac);
	while (i < ac) {
		printf("av[%i]: %s\n", i, av[i]);
		i++;
	}
}
