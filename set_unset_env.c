#include "main.h"

/**
 * get_linked_list_var - gives the variable name of each node
 * @curr_node:  current node of linked list
 * Return: the variable name
 */

char *get_linked_list_var(node *curr_node)
{
	char *name;
	int len, i;

	len = _strlen(curr_node->data);
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
 * @var: the varibale
 * @value: the value
 * @head: the head node
 * Return: 0 or -1
 */

int set_env(char *var, char *value, node **head)
{
	node *env_list;
	char *name, *val = NULL;
	int len;

	env_list = *head;
	val = malloc(sizeof(char) * (_strlen(var) + _strlen(value) + 2));
	if (val == NULL)
		return (-1);
	_strcpy(val, var);
	_strcat(val, "=");
	_strcat(val, value);
	val[_strlen(val)] = '\0';

	while (env_list != NULL)
	{
		if (env_list->data == NULL)
		{
			perror("env_list");
			return (-1);
		}
		else
		{
			name = get_linked_list_var(env_list);
			if (_strcmp(name, var) == 0)
			{
				free(env_list->data);
				env_list->data = _strdup(val);
				env_list->len = _strlen(val);
				free(val);
				free(name);
				return (1);
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
 * @var: the variable of the environment that will be removed
 * @head: the head node
 * Return: 0 or -1
 */

int unset_env(char *var, node **head)
{
	node *env_list;
	char *name, *val;
	int len, i = 0, check;

	env_list = *head;
	while (env_list != NULL)
	{
		i++;
		if (env_list->data == NULL)
		{
			perror("env_list");
			return (-1);
		}
		else
		{
			name = get_linked_list_var(env_list);
			if (_strcmp(name, var) == 0)
			{
				check = delete_node_at_index(head, i - 1);
				free(name);
				if (check == 1)
					return (0);
				else if (check == -1)
				{
					perror("node not fount");
					return (-1);
				}
			}
		}
		free(name);
		env_list = env_list->next;
	}
	return (-1);
}
