#include "main.h"

/**
 * parse_string - parse a string according to a delimiter
 * @lineptr: input string
 * @delim: delimeter
 * Return: array of pointer characters to the parsed string
*/

char **parse_string(char *lineptr, char *delim)
{
	char *token, *input, *cpy_input;
	char **arg;
	int no_tokens = 0, i = 0;

	input = malloc(sizeof(char) * (_strlen(lineptr) + 1));
	_strcpy(input, lineptr);

	cpy_input = malloc(sizeof(char) * (_strlen(lineptr) + 1));
	_strcpy(cpy_input, input);

	token = _strtok(input, delim);
	while (token != NULL)
	{
		no_tokens++;
		token = _strtok(NULL, delim);
	}

	arg = malloc(sizeof(char *) * (no_tokens + 1));

	token = _strtok(cpy_input, delim);
	while (token)
	{
		arg[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(arg[i++], token);
		token = _strtok(NULL, delim);
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
	int exec = 0, status;

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
				exec = 2;
				_exit(exec);
			}
		}
		else
		{
			wait(&status);
			exec = WEXITSTATUS(status);
		}
		return (exec);
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
 * @fd: file descriptor
 * Return: pointer to buffer that has the input
*/
char *read_for_noninteractive(ssize_t fd)
{
	char *buffer = NULL;
	size_t buffer_size = 0, size = 1024;
	ssize_t rd;

	buffer = malloc(sizeof(char) * (size + 1));
	while ((rd = read(fd, buffer + buffer_size, size)) > 0)
	{

		buffer_size += rd;

		if (buffer_size >= size)
		{
			size *= 2;
			buffer = _realloc(buffer, sizeof(char) * buffer_size,
				sizeof(char) * size);
		}
	}

	if (rd == -1)
	{
		perror("read");
		free(buffer);
		return (NULL);
	}

	buffer[buffer_size - 1] = '\0';

	return (buffer);
}

/**
 * handle_exit_err - handle errors for exit built-in
 * @arr: array of parsed strings
 * @argv: argument list that comes from main
 * @lineptr: buffer that be read from getline
 * @env_list: linked list for environment variables
 * @sequences: array of pointers to sequences commands
 * Return: return value of exit
*/

int handle_exit_err (char **arr, char **argv, char *lineptr, node *env_list, char **sequences)
{
	int ret = 0;

	if (atoi(arr[1]) < 0)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": exit: Illegal number: ", 25);
		write(STDERR_FILENO, arr[1], _strlen(arr[1]));
		write(STDERR_FILENO, "\n", 1);
		ret = 1;
		free_arr(arr);
	}
	else if (_atoi(arr[1]) >= 0 && _atoi(arr[1]) <= 255)
	{
		ret = _atoi(arr[1]);
		free_arr(arr);
		free(lineptr);
		free_list(env_list);
		free_arr(sequences);
		exit(ret);
	}
	else
	{
		ret = _atoi(arr[1]) - 256;
		free_arr(arr);
		free(lineptr);
		free_list(env_list);
		free_arr(sequences);
		exit(ret);
	}

	return (ret);
}
