#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

#define UNUSED(x) (void)(x)

extern char **environ;

/**
 * struct node - linked list of the environment
 * @data: string
 * @len: length of the string
 * @next: points to the next node
 */

typedef struct node
{
	char *data;
	unsigned int len;
	struct node *next;
} node;

/**
 * struct built_in - struct of built-ins with their functions
 * @command: built-in command
 * @func: pointer to function that implement the buit-in
 */
typedef struct built_in
{
	char *command;
	int (*func)(char *var, char *value, node **head);
} builtin;

int interactive(char **argv, char **envp, node *env_list);
int non_interactive(char **argv, char **envp, node *env_list);
int file_command(char **argv, char **envp, node *env_list);

char **parse_string(char *lineptr, char *delim);
int execute(char **args, char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *read_for_noninteractive(ssize_t fd);
int handle_exit_err (char **arr, char **argv, char *lineptr, node *env_list);

int is_exit(char **arr, char *lineptr, char **argv, int ret, node *env_list);
int check_command(char **arr, char **envp, char **argv, int history);
int check_builtins(node *env_list, char **arr, int *ret);
void check_null(char *command, char **arr, int *is_builtin);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int ind);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);

int _atoi(char *str);
char *_strdup(char *str);
char *tostring(int num);
int strnum(char **arr);

char *_strtok(char *str, const char *delim);

char *get_path(char **envp);
char **get_dirs(char *path);
char *file_dir(char **dirs, char *file_name);
void free_arr(char **arr);

node *add_node_end(node **head, char *str);
size_t print_list(const node *h);
void free_list(node *head);
int delete_node_at_index(node **head, unsigned int index);

node *get_env_list(char **env);
int _env(char *var, char *value, node **head);

char *get_linked_list_var(node *curr_node);
int set_env(char *var, char *value, node **head);
int unset_env(char *var, char *value, node **head);

#endif
