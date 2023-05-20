#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * struct node - linked list of the environment
 * @data: string
 * @len: length of the string
 * @next: points to the next node
 */

typedef struct node {
	char *data;
        unsigned int len;
	struct node *next;
} node;


/**
 * get_env - get the environment
 * Return: 2D array of environment arguments
 */

char **get_env(void)
{
	char **curr;

	curr = environ;
	return (curr);
}

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

void _env(node *head)
{
	print_list(head);
}

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


int main(void)
{
	node *env_list, *after;
	const char *home = getenv("HOME");
	const char *new_home;
	char **curr_env;  

	curr_env = get_env();
	env_list = get_env_list(curr_env);

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
