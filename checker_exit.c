#include "main.h"

/**
 * checker_exit - to checks if the user entered the 'exit' command.
 * @line: User input.
 * Return: 1 if the user entered the 'exit' command, 0 if not.
 */
int checker_exit(char *line)
{
size_t i;

for (i = 0; i < 4; i++)
{
if (line[i] != "exit"[i])
break;
}
if (i == 4 && line[4] == '\0')
return (1);
else
return (0);
}
