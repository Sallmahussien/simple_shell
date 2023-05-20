#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int interactive(char **argv, char **envp);
int non_interactive(char **argv, char **envp);

char **parse_string(char *lineptr, char *delim);
int execute(char **args, char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *read_for_noninteractive(void);
int handle_exit_err(char **arr, char **argv, char *lineptr);

int is_exit(char **arr, char *lineptr, char **argv, int ret);
int check_command(char **arr, char **envp, char **argv, int history);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int ind);
int _strcmp(char *s1, char *s2);
int _atoi(char *str);
char *_strcat(char *dest, char *src);
char *tostring(int num);

char *_strtok(char *str, const char *delim);

char *get_path(char **envp);
char **get_dirs(char *path);
char *file_dir(char **dirs, char *file_name);
void free_arr(char **arr);

#endif
