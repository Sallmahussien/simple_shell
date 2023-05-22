#include "main.h"

/**
 * check_change_dir - checks if change dir == 0 or not
 * @curr_cwd: current cwd
 * @new_dir: the new dir will be moved to
 * @name: variable name in linked list
 * @head: head node of linked list
 * Return: 0 or 1
 */

int check_change_dir(char *curr_cwd, char *new_dir, char *name, node **head, char **argv, char **arr, int history)
{
	node *env_list;

	env_list = *head;
	if (change_dir(new_dir, curr_cwd, &env_list, argv, arr, history) == 0)
	{
		free(name);
		free(new_dir);
		return (0);
	}
	else
	{
		free(name);
		free(new_dir);
		return (2);
	}
}


/**
 * null_dir - move to home directory
 * @head: head node of environment linked list
 * @curr_cwd: current cwd
 * Return: 0 or 1
 */

int null_dir(char *curr_cwd, node **head, char **argv, char **arr, int history)
{
	node *env_list = *head;
	char *new_dir = NULL, *name;
	int i, ii = 0;

	while (env_list != NULL)
	{
		if (env_list->data == NULL)
		{
			perror("env_list");
			return (2);
		}
		else
		{
			name = get_linked_list_var(env_list);
			if (_strcmp(name, "HOME") == 0)
			{
				new_dir = malloc(sizeof(char) * (_strlen(env_list->data) - 4));
				if (new_dir == NULL)
				{
					perror("malloc");
					return (2);
				}
				for (i = 5; env_list->data[i]; i++)
					new_dir[ii++] = env_list->data[i];
				new_dir[ii] = '\0';
				if (check_change_dir(curr_cwd, new_dir, name, &env_list, argv, arr, history) == 0)
					return (0);
				else
					return (2);
			}
		}
		free(name);
		free(new_dir);
		env_list = env_list->next;
	}
	return (2);
}


/**
 * past_dir - move to home directory
 * @head: head node of environment linked list
 * @curr_cwd: current cwd
 * Return: 0 or 2
 */

int past_dir(char *curr_cwd, node **head, char **argv, char **arr, int history)
{
	node *env_list = *head;
	char *new_dir = NULL, *name;
	int i, ii = 0;

	while (env_list != NULL)
	{
		if (env_list->data == NULL)
		{
			perror("env_list\n");
			return (2);
		}
		else
		{
			name = get_linked_list_var(env_list);
			if (_strcmp(name, "OLDPWD") == 0)
			{
				new_dir = malloc(sizeof(char) * (_strlen(env_list->data) - 6));
				if (new_dir == NULL)
				{
					perror("malloc");
					return (2);
				}
				for (i = 7; env_list->data[i]; i++)
					new_dir[ii++] = env_list->data[i];
				new_dir[ii] = '\0';
				write(STDOUT_FILENO, new_dir, _strlen(new_dir));
				write(STDOUT_FILENO, "\n", 1);
				if (check_change_dir(curr_cwd, new_dir, name, &env_list, argv, arr, history) == 0)
					return (0);
				else
					return (2);			}
		}
		free(name);
		free(new_dir);
		env_list = env_list->next;
	}
	return (2);
}

/**
 * back_dir - change dir step back
 * @curr_cwd: current cwd
 * @head: head node of linked list
 * Return: 0 or 2
 */

int back_dir(char *curr_cwd, node **head, char **argv, char **arr, int history)
{
	node *env_list;
	char *new_dir;
	int i, len = 0, count = 0, num = 0;

	env_list = *head;
	for (i = 0; curr_cwd[i] != '\0'; i++)
	{
		if (curr_cwd[i] == '/')
			count++;
	}
	for (i = 0; curr_cwd[i] != '\0'; i++)
	{
		if (curr_cwd[i] == '/')
			num++;
		if (num == count)
			break;
	}
	len = i;
	new_dir = malloc(sizeof(char) * (len + 1));
	for (i = 0; i < len; i++)
		new_dir[i] = curr_cwd[i];
	new_dir[i] = '\0';
	if (change_dir(new_dir, curr_cwd, &env_list, argv, arr, history) == 0)
	{
		free(new_dir);
		return (0);
	}
	else
	{
		free(new_dir);
		return (2);
	}
}
