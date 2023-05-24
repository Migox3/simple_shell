#include "main.h"

/**
 * absolu_exec - Executes a command specified with an absolute path.
 * @args: An array of command-line arguments,
 * where the first argument is the command to execute
 * and subsequent arguments are its arguments.
 * @prog_name: The name of the program (used for error messages).
 */

void absolu_exec(char *args[], char *prog_name)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (access(args[0], X_OK) == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
		execve(args[0], args, environ);
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}
