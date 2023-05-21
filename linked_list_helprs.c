/**
 * *add_node_end - function that adds a new node at the end of a list.
 * @head: pointer to the head
 * @str: string
 * Return: the address of the new element, or NULL if it failed
 */

node *add_node_end(node **head, char *str)
{
	node *new_node, *temp;
	unsigned int len = 0;

	new_node = malloc(sizeof(node));
	if (new_node == NULL)
		return (NULL);

	len = _strlen(str);

	new_node->data = _strdup(str);
	if (new_node->data == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->len = len;
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
 * print_list - function that prints all the elements of a list_t list.
 * @h: a singly linked list
 * Return: the number of nodes
 */

size_t print_list(const node *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		if (h->data == NULL)
		{
			perror("node->str");
			return (-1);
		}
		else
		{
			write(STDOUT_FILENO, h->data, h->len);
			write(STDOUT_FILENO, "\n", 1);
		}
		count++;
		h = h->next;
	}

	return (count);
}

/**
 * free_list - function that frees a list_t list
 * @head: pointer to the head of the list
 * Return: void
 */

void free_list(node *head)
{
	node *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

/**
 * delete_node_at_index - deletes the node at index index of a listint_t.
 * @head: pointer to the address of list head
 * @index: list index to be deleted
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_node_at_index(node **head, unsigned int index)
{
	node *current, *tmp;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
		return (-1);

	if (index == 0)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->data);
		free(tmp);
		return (1);
	}

	current = *head;
	while (current)
	{
		if (index == (i + 1))
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->data);
			free(tmp);
			return (1);
		}
		current = current->next;
		i++;
	}
	return (-1);
}
