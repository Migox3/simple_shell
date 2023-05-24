#ifndef _MAIN_H_
#define _MAIN_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3


extern char **enviro;


/**
 * struct list_s - A new struct type defining a linked list.
 * @dirp: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dirp;
	struct list_s *next;
} list_t;

/**
 * struct builtin - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;



ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);


void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);



void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void _all(void);
void _alias(void);
void _cd(void);
void _exit(void);
void _help(void);
void _env(void);
void _setenv(void);
void _unsetenv(void);
void _history(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif
