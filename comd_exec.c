#include "main.h"

void comd_exec(char *args[], char *prog_name);

/**
 * comd_exec - Executes a command with arguments.
 * @args: An array of command-line arguments,
 * where the first argument is the command to execute
 * and subsequent arguments are its arguments.
 * @prog_name: The name of the program (used for error messages).
 */

void comd_exec(char *args[], char *prog_name)

{
	int i;

	for (i = 0; args[0][i] == ' '; i++)
	{
		continue;
	}
	for (i = strlen(args[0]) - 1; i >= 0 && args[0][i] == ' '; i--)
	{
		args[0][i] = '\0';
	}
	if (strchr(args[0], '/') != NULL)
	{
		absolu_exec(args, prog_name);
	}
	else
	{
		path_exec(args, prog_name);
	}
}
