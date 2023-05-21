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

int _env(char *var, char *value, node *head)
{
	UNUSED(var);
	UNUSED(value);
	print_list(head);
	return (0);
}



int main(void)
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
}
