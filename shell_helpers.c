#include "main.h"

/**
 * parse_string - parse a string according to a delimiter
 * @lineptr: input string
 * Return: array of pointer characters to the parsed string
*/

char **parse_string(char *lineptr)
{
	char *token, *input, *cpy_input;
	char **arg;
	int no_tokens = 0, i = 0;

	input = malloc(sizeof(char) * (strlen(lineptr) + 1));
	strcpy(input, lineptr);

	cpy_input = malloc(sizeof(char) * (strlen(lineptr) + 1));
	strcpy(cpy_input, input);

	token = strtok(input, " ");
	while (token != NULL)
	{
		no_tokens++;
		token = strtok(NULL, " ");
	}

	arg = malloc(sizeof(char *) * (no_tokens + 1));

	token = strtok(cpy_input, " ");
	while (token)
	{
		arg[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(arg[i++], token);
		token = strtok(NULL, " ");
	}
	arg[i] = NULL;

	free(input);
	free(cpy_input);

	return (arg);
}

/**
 * execute - execute the command with arguments
 * @args: array to character pointers to command and argument
 * @argv: array of pointers to arguments from main func
 * Return: -1 on error and 0 on sucess
*/
int execute(char **args, char **argv)
{
	pid_t pid;

	pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			return (-1);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror(argv[0]);
				return (-1);
			}
		}
		else
		{
			wait(NULL);
		}
		return (0);
}

/**
 * _realloc -  reallocates a memory block using malloc and free.
 * @ptr:  pointer to the memory previously allocated with a call to malloc.
 * @old_size: old_size.
 * @new_size: new size, in bytes of the new memory block.
 * Return: pointer to new allocated mem
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *arr;
	char *mem, *ptrcp;
	unsigned int i;

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
	{
		arr = malloc(new_size);
		if (arr == NULL)
			return (NULL);
		return (arr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size > old_size)
	{
		ptrcp = ptr;
		mem = malloc(new_size);
		if (mem == NULL)
		{
			free(ptr);
			return (NULL);
		}

		arr = mem;

		for (i = 0; i < old_size; i++)
			mem[i] = ptrcp[i];

		free(ptr);
	}
	return (arr);
}

/**
 * read_for_noninteractive - read the input for non-interactive mode
 * Return: pointer to buffer that has the input
*/
char *read_for_noninteractive(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0, size = 1024;
	ssize_t rd;

	buffer = malloc(sizeof(char) * size);
	while ((rd = read(STDIN_FILENO, buffer + buffer_size, size)) > 0)
	{
		if (rd == -1)
		{
			perror("read");
			return (NULL);
		}

		buffer_size += rd;

		if (buffer[buffer_size - 1] == '\n')
			break;

		if ((size_t) rd == size)
		{
			buffer = _realloc(buffer, sizeof(char) * buffer_size,
				sizeof(char) * buffer_size * 2);
		}
	}

	buffer[buffer_size - 1] = '\0';

	return (buffer);
}
