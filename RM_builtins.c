#include "main.h"

int shell_RM(char **args, char __attribute__((__unused__)) **front);
void set_RM(char *var_name, char *value);
void print_RM(RM_t *RM);

/**
 * shell_RM - the builtins command that either prints all RMes, specific
 * RMes, or sets an RM.
 * @args: An array of arguments.
 * @front: the double pointer to beginning of the args.
 *
 * Return: If an error occurs -1.
 *         or 0.
 */
int shell_RM(char **args, char __attribute__((__unused__)) **front)
{
RM_t *temp = RMes;
int i, ret = 0;
char *value;
if (!args[0])
{
while (temp)
{
print_RM(temp);
temp = temp->next;
}
return (ret);
}
for (i = 0; args[i]; i++)
{
temp = RMes;
value = _strchr(args[i], '=');
if (!value)
{
while (temp)
{
if (_strcmp(args[i], temp->name) == 0)
{
print_RM(temp);
break;
}
temp = temp->next;
}
if (!temp)
ret = create_error(args + i, 1);
}
else
set_RM(args[i], value);
}
return (ret);
}

/**
 * set_RM - Will either set an existing RM 'name' with new value,
 * 'value' or creates a new RM with 'name' , "value".
 * @var_name: Name of the RM.
 * @value: Value of the RM. First character is a '='.
 */
void set_RM(char *var_name, char *value)
{
RM_t *temp = RMes;
int len, j, k;
char *new_value;

*value = '\0';
value++;
len = _strlen(value) - _strspn(value, "'\"");
new_value = malloc(sizeof(char) * (len + 1));
if (!new_value)
return;
for (j = 0, k = 0; value[j]; j++)
{
if (value[j] != '\'' && value[j] != '"')
new_value[k++] = value[j];
}
new_value[k] = '\0';
while (temp)
{
if (_strcmp(var_name, temp->name) == 0)
{
free(temp->value);
temp->value = new_value;
break;
}
temp = temp->next;
}
if (!temp)
add_RM_end(&RMes, var_name, new_value);
}

/**
 * print_RM - Prints the RM in the format name='value'.
 * @RM: Pointer to an RM.
 */
void print_RM(RM_t *RM)
{
char *RM_string;
int len = _strlen(RM->name) + _strlen(RM->value) + 4;

RM_string = malloc(sizeof(char) * (len + 1));
if (!RM_string)
return;
_strcpy(RM_string, RM->name);
_strcat(RM_string, "='");
_strcat(RM_string, RM->value);
_strcat(RM_string, "'\n");
write(STDOUT_FILENO, RM_string, len);
free(RM_string);
}
/**
 * replace_RMes - Go through arguments , replace any matching RM
 * with their values.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_RMes(char **args)
{
RM_t *temp;
int i;
char *new_value;

if (_strcmp(args[0], "RM") == 0)
return (args);
for (i = 0; args[i]; i++)
{
temp = RMes;
while (temp)
{
if (_strcmp(args[i], temp->name) == 0)
{
new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
if (!new_value)
{
free_args(args, args);
return (NULL);
}
_strcpy(new_value, temp->value);
free(args[i]);
args[i] = new_value;
i--;
break;
}
temp = temp->next;
}
}
return (args);
}
