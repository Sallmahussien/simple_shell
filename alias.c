#include "main.h"

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


/**
 * print_ali - function that prints all the elements of an ali list.
 * @h: a singly linked list
 * Return: the number of nodes
 */

size_t print_ali(const ali *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		if (h->name == NULL || h->value == NULL)
		{
			perror("node->");
			return (-1);
		}
		else
		{
			write(STDOUT_FILENO, h->name, _strlen(h->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, h->value, _strlen(h->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		count++;
		h = h->next;
	}

	return (count);
}

/**
 * *add_ali_end - function that adds a new node at the end of a list.
 * @head: pointer to the head
 * @name: alias name
 * @value: alias value
 * Return: the address of the new element, or NULL if it failed
 */

ali *add_ali_end(ali **head, char *name, char *value)
{
	ali *new_node, *temp;

	new_node = malloc(sizeof(ali));
	if (new_node == NULL)
		return (NULL);

	new_node->name = _strdup(name);
	if (new_node->name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = _strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node->name);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;

	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}


	return (*head);
}

/**
 * free_ali - function that frees a list_t list
 * @head: pointer to the head of the list
 * Return: void
 */

void free_ali(ali *head)
{
	ali *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

/**
 * _alias - set new alias and print alias ang get a value of alias name
 * @arg: alias argument
 * @head: linked list of aliases
 * Return: value of alias name or NULL
 */

char *_alias(char *arg, ali **head)
{
	char *token, *name, *value;
	int i = 0, flag = 0;

	if (arg == NULL)
	{
		print_ali(*head);
		return (NULL);
	}
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
	{
		token = _strtok(arg, "=");
		name = _strdup(token);
		token = _strtok(NULL, "=");
		value = _strdup(token);
		add_ali_end(head, name, value);
		free(name);
		free(value);
		return (NULL);
	}
	else
	{
		while (*head)
		{
			if ((*head)->name == NULL || (*head)->value == NULL)
			{
				perror("list");
				return (NULL);
			}
			if (_strcmp(arg, (*head)->name) == 0)
				return ((*head)->value);
		}
	}
}

/**int main(int argc, char **argv)
{
  ali *list = NULL;
  char arg[]= "l=ls", arg1[]="ll=ls -l", *value;

  _alias(arg, &list);
  _alias(arg1, &list);
  value = _alias("l", &list);
  printf("value of l = %s\n", value);
  _alias(NULL, &list);

  print_ali(list);

  free_ali(list);
  return (0);
  }*/
