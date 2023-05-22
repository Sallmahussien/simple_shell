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
 * @head: linked list
 */

int _env(char *var, char *value __attribute__((unused)), node **head, char **argv, char **arr, int history)
{
	node *h = *head;

	UNUSED(var);
	UNUSED(value);
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
 * @histor: history
 * return: -1
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
	write(STDERR_FILENO, " can't add/remove from the environ\n",35);
	free(err);
	return (-1);
}


/*int main(void)
{
	node *env_list, *after;
	const char *home = getenv("HOME");
	const char *new_home;
	char **curr_env;  

	env_list = get_env_list(environ);

	_env(env_list);

	printf("\n\n********************\n\n");

	printf("original home = %s\n", home);
	set_env("HOME", "sweet home", &env_list);

	printf("\n\n********************\n\n");

	printf("\n\n********************\n\n");
	set_env("salma", "ahmed", &env_list);
	printf("done\n");
	_env(env_list);
	printf("\n\n********************\n\n");

	unset_env("salma", &env_list);
	_env(env_list);
  
	free_list(env_list);
  
	return (0);
}*/
