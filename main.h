#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int interactive(char **argv);
int non_interactive(char **argv);

char **parse_string(char *lineptr);
int execute(char **args, char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *read_for_noninteractive(void);
int handle_exit_err (char **arr, char **argv, char *lineptr);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int ind);
int _strcmp(char *s1, char *s2);
int _atoi(char *str);

char *_strtok(char *str, const char *delim);

#endif
