#include "main.h"

/**
 * get_env_list - creat a linked list of the environment
 * @env: 2D array of environment arguments
 * Return: linked list
 */

node *get_env_list(char **env)
{
	node *head;

	head = NULL;
	while (*env)
	{
		head = add_node_end(&head, *env);
		env++;
	}

	return (head);
}
/**
 * _env - prints the environment
 * @head: linked list for the environment variables
 * @argv: array of character pointer to arguments from main
 * @arr: array of character pointers to parsed string
 * @history: history
 * Return: 0
 */

int _env(node **head, char **argv, char **arr, int history)
{
	node *h = *head;

	UNUSED(argv);
	UNUSED(arr);
	UNUSED(history);

	print_list(h);
	return (0);
}

/**
 * env_err - create error message for env
 * @argv: array of pointers to arguments from main
 * @arr: array of pointers to parsed string
 * @history: history
 * Return: -1 on failure
 */
int env_err(char **argv, char **arr, int history)
{
	char *err;

	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	err = tostring(history);
	write(STDERR_FILENO, err, _strlen(err));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arr[0], _strlen(arr[0]));
	write(STDERR_FILENO, " can't add/remove from the environ\n", 35);
	free(err);
	return (-1);
}
