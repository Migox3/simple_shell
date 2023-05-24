#include "main.h"

void sig_hand(int sig);
int execute(char **args, char **front);

/**
 * sig_hand - is the Prints of a new prompt upon a signal.
 * @sig: signals.
 */
void sig_hand(int sig)
{
char *new_prompt = "\n$ ";

(void)sig;
signal(SIGINT, sig_hand);
write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - to Executes a command in the child process.
 * @args: array of arguments.
 * @front: double pointer to the beginning of args.
 *
 * Return: If the error occurs - a corresponding error code.
 *         O/W - to exit value of the executed command.
 */
int execute(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];
if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = get_location(command);
}
if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (create_error(args, 126));
else
ret = (create_error(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
execve(command, args, NULL);
if (errno == EACCES)
ret = (create_error(args, 126));
free_env();
free_args(args, front);
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}

/**
 * main - it runs the simple UNIX command interpreter.
 * @argc: for the number of arguments supplied to the program.
 * @argv: for the array of pointers to the arguments.
 *
 * Return: The return value of the executed command.
 */
int main(int argc, char *argv[])
{
int ret = 0, retn;
int *exe_ret = &retn;
char *prompt = "$ ", *new_line = "\n";

signal(SIGINT, sig_hand);
*exe_ret = 0;
if (argc != 1)
{
ret = proc_file_commands(argv[1], exe_ret);
free_env();
return (*exe_ret);
}
if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handle_args(exe_ret);
free_env();
return (*exe_ret);
}
while (1)
{
write(STDOUT_FILENO, prompt, 2);
ret = handle_args(exe_ret);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 1);
free_env();
exit(*exe_ret);
}
}
free_env();
return (*exe_ret);
}
