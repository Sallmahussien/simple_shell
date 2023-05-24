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
	int (*func)(node **head, char **argv, char **arr, int history);
} builtin;

/**
 * struct ali - linked list of the environment
 * @name: alias name
 * @value: alias value
 * @next: points to the next node
 */

typedef struct ali
{
	char *name;
	char *value;
	struct ali *next;
} ali;

int interactive(char **argv, char **envp, node *env_list, ali *list);
int non_interactive(char **argv, char **envp, node *env_list, ali *list);
int file_command(char **argv, char **envp, node *env_list, ali *list);

char **parse_string(char *lineptr, char *delim);
int execute(char **args, char **argv, int history, char *arg_path,
char **envp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *read_for_noninteractive(ssize_t fd);
int handle_exit_err(char **arr, char **argv, char *lineptr, node *env_list,
		char **sequences, int *exec, char **commands, int history);

int is_exit(char **arr, char *lineptr, char **argv, int *exec, node *env_list,
char **sequences, char **commands, int history);
int check_command(char **arr, char **envp, char **argv, int history,
int *exec);
int check_builtins(node *env_list, char **arr, int *ret, char **argv,
int history);
void check_null(char *command, char **arr, int *is_builtin);

void free_interactive(char *lineptr, node *env_list, ali *list);
void free_noninteractive(char **commands, char *buffer, node *env_list);
void shell_help(char **sequences, char *lineptr, char **argv, char **envp,
int *exec, node *env_list, int *history, char **commands);
void open_err(char **argv, int *history, node *env_list);
ssize_t read_from_file(ssize_t op, char *buffer, node *env_list);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int ind);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);

int _atoi(char *str);
char *_strdup(char *str);
char *tostring(int num);
int strnum(char **arr);

char *_strtok(char *str, char *delim);

char *get_path(char **envp);
char **get_dirs(char *path);
char *file_dir(char **dirs, char *file_name);
void free_arr(char **arr);

node *add_node_end(node **head, char *str);
size_t print_list(const node *h);
void free_list(node *head);
int delete_node_at_index(node **head, unsigned int index);

node *get_env_list(char **env);
int _env(node **head, char **argv, char **arr, int history);
int env_err(char **argv, char **arr, int history);

char *get_linked_list_var(node *curr_node);
int set_env(node **head, char **argv, char **arr, int history);
int unset_env(node **head, char **argv, char **arr, int history);

int change_dir(char *dir,  char *curr_cwd, node **head, char **argv,
char **arr, int history);
int change_dir_direct(char *dir, char *curr_cwd, node **head, char **argv,
char **arr, int history);
int _cd(node **head, char **argv, char **arr, int history);

int check_change_dir(char *curr_cwd, char *new_dir, char *name, node **head,
char **argv, char **arr, int history);
int null_dir(char *curr_cwd, node **head, char **argv, char **arr,
int history);
int past_dir(char *curr_cwd, node **head, char **argv, char **arr,
int history);
int back_dir(char *curr_cwd, node **head, char **argv, char **arr,
int history);

size_t print_ali(const ali *h);
ali *add_ali_end(ali **head, char *name, char *value);
void free_ali(ali *head);
int _alias(char *arg, ali **head);

#endif
