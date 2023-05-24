#include "main.h"

/**
 * path_exec - Execute the command specified by searching the PATH.
 * @args: An array of command_line arguments,
 * where the 1st argument is the command to be executed
 * and subsequent arguments are arguments.
 * @program_name: The name of the program .
 */

void execPath(char *args[], char *program_name)
{
pid_t pid;
char command_path[1024];
char *path = getenv("PATH");
char *pathCopy = strdup(path);
char *token, *p = pathCopy;
int cmd_exists = 0;

while ((token = strtok(p, ":")) != NULL)
{
p = NULL;
snprintf(command_path, sizeof(command_path), "%s/%s", token, args[0]);
if (access(command_path, X_OK) == 0)
{
cmd_exists = 1;
break;
}
}
free(pathCopy);
if (!cmd_exists)
{
perror(program_name);
return;
}
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
execve(command_path, args, environ);
perror(program_name);
exit(EXIT_FAILURE);
}
wait(NULL);
}
