#ifndef _MAIN_H_
#define _MAIN_H_

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void path_exec(char *args[], char *prog_name);
void comd_exec(char *args[], char *prog_name);
int cd_comd(char *args[]);
void absolu_exec(char *args[], char *prog_name);
int exit_check(char *line);

extern char **environ;

#define MAX_COMMAND 50

#endif
