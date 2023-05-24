#include "main.h"

int check_exit(char *line);
int check_cd(char **args);

/**
 * main - A UNIX command_line interpreter.
 * @argc: argument count
 * @argv: argument vector storing the program name at 0 index
 * Return: 0 when it go well
 */
int main(int __attribute__((unused)) argc, char **argv)
{
size_t j, len = 0;
char *token, *line = NULL;
char *args[MAX_COMMAND / 2 + 1];
ssize_t read;
int interactive = isatty(STDIN_FILENO);

while (1)
{
j = 0;
if (interactive)
{
printf("\033[32mSimple-Shell$\033[0m ");
fflush(stdout);
}
read = getline(&line, &len, stdin);
if (read == -1)
{
break;
}
token = strtok(line, " ");
while (token != NULL && j < MAX_COMMAND / 2)
{
args[j++] = token;
token = strtok(NULL, " ");
}
args[j] = NULL;
line[read - 1] = '\0';
if (j > 0)
args[0] = args[0];
else
args[0] = line;
if (check_exit(line))
break;
if (check_cd(args))
continue;
comd_exec(args, argv[0]);
}
free(line);
exit(EXIT_SUCCESS);
}

/**
 * checker_exit - to checks if the user input is an exit command or no.
 * @line: Pointer to the user input string.
 * Return: 1 if the input is an exit command, 0 if not.
 */
int checker_exit(char *line)
{
return (checker_exit(line));
}

/**
 * check_cd - to checks if the user input is a cd command.
 * @args: An array of pointers to strings containing the user input.
 * Return: 1 if the input is a cd command, 0 if not.
 */
int check_cd(char **args)
{
if (strcmp(args[0], "cd") == 0)
{
cd_comd(args);
return (1);
}
return (0);
}
