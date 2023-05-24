#include "main.h"

/**
 * cd_comd - Changes the current directory .
 * @args: An array of command-line arguments,
 * where the first argument is the command to execute
 * and its arguments are the subsequent arguments.
 * Return: 0 if successful, -1 if an error occurs.
 */
int cd_comd(char *args[])
{
	char *dir = args[1] != NULL ? args[1] : getenv("HOME");
	char *currentDir;


	if (dir == NULL)
	{
		return (-1);
	}
	if (strcmp(dir, "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (dir == NULL)
		{
			perror("cd");
			return (-1);
		}
		printf("%s\n", dir);
	}
	currentDir = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		perror("cd");
		return (-1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", currentDir, 1);
	free(currentDir);
	return (0);
}
