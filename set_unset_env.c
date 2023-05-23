#include "main.h"

/**
 * get_linked_list_var - gives the variable name of each node
 * @curr_node:  current node of linked list
 * Return: the variable name
 */

char *get_linked_list_var(node *curr_node)
{
	char *name;
	int i;

	/*len = _strlen(curr_node->data);*/
	for (i = 0; curr_node->data[i] != '='; i++)
		;
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		return (0);
	for (i = 0; curr_node->data[i] != '='; i++)
		name[i] = curr_node->data[i];
	name[i] = '\0';

	return (name);
}

/**
 * set_env - change or add an environment variable
 * @head: the head node
 * @argv: array of character pointers to the arguments from main
 * @arr: array of character pinter to parsed string
 * @history: history
 * Return: 0 or -1
 */

int set_env(node **head, char **argv, char **arr, int history)
{
	node *env_list;
	char *name, *val = NULL;

	if (strnum(arr) != 3)
		return (env_err(argv, arr, history));

	env_list = *head;
	val = malloc(sizeof(char) * (_strlen(arr[1]) + _strlen(arr[2]) + 2));
	if (val == NULL)
		return (env_err(argv, arr, history));
	_strcpy(val, arr[1]);
	_strcat(val, "=");
	_strcat(val, arr[2]);
	val[_strlen(val)] = '\0';
	while (env_list != NULL)
	{
		if (env_list->data == NULL)
		{
			perror("env_list");
			return (env_err(argv, arr, history));
		}
		else
		{
			name = get_linked_list_var(env_list);
			if (_strcmp(name, arr[1]) == 0)
			{
				free(env_list->data);
				env_list->data = _strdup(val);
				env_list->len = _strlen(val);
				free(val);
				free(name);
				return (0);
			}
			free(name);
		}
		env_list = env_list->next;
	}
	add_node_end(head, val);
	free(val);
	return (0);
}

/**
 * unset_env - Remove an environment variable
 * @head: the head node
 * @argv: array of character pointers to the arguments from main
 * @arr: array of character pinter to parsed string
 * @history: history
 * Return: 0 or -1
 */

int unset_env(node **head, char **argv, char **arr, int history)
{
	node *env_list;
	char *name;
	int i = 0, check;

	if (strnum(arr) != 2)
		return (env_err(argv, arr, history));
	env_list = *head;
	while (env_list != NULL)
	{
		i++;
		if (env_list->data == NULL)
			return (env_err(argv, arr, history));

		name = get_linked_list_var(env_list);
		if (_strcmp(name, arr[1]) == 0)
		{
			check = delete_node_at_index(head, i - 1);
			free(name);
			if (check == 1)
				return (0);
			else if (check == -1)
			{
				return (env_err(argv, arr, history));
			}
		}
		free(name);
		env_list = env_list->next;
	}
	return (env_err(argv, arr, history));
}
