#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);


void print_arg(char* arg);
void print_args(int ac, char** av);


int main(void)
{√
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
