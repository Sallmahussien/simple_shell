#include "main.h"

/**
 * interactive - execute shell in the interactive mode
 * @argv: array of pointers to arguments
 * Return: the return value of the execution
*/
int interactive(char **argv)
{
	ssize_t p;
	size_t n = 0;
	char *lineptr = NULL;
	char **arr;
	int i, exec, ret = 0;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		p = getline(&lineptr, &n, stdin);
		if (p == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		lineptr[p - 1] = '\0';

		arr = parse_string(lineptr);

		if (_strcmp(arr[0], "exit") == 0 && arr[1] == NULL)
		{
			for (i = 0; arr[i]; i++)
				free(arr[i]);
			free(arr);
			free(lineptr);
			exit(ret);
		}
		else if (_strcmp(arr[0], "exit") == 0 && arr[1] != NULL)
		{
			ret = handle_exit_err(arr, argv, lineptr);
			if (ret == 0)
				continue;
		}

		exec = execute(arr, argv);

		ret = exec;

		for (i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}

	free(lineptr);

	return (ret);
}

/**
 * non_interactive - execute shell in the non-interactive mode
 * @argv: array of pointers to arguments
 * Return: the return value of the execution
*/
int non_interactive(char **argv)
{
	char *buffer;
	char **arr;
	int exec, i, ret = 0;

	buffer = read_for_noninteractive();

	arr = parse_string(buffer);

	if (_strcmp(arr[0], "exit") == 0 && arr[1] == NULL)
	{
		for (i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
		free(buffer);
		exit(ret);
	}
	else if (_strcmp(arr[0], "exit") == 0 && arr[1] != NULL)
	{
		ret = handle_exit_err(arr, argv, buffer);
		return (ret);
	}

	exec = execute(arr, argv);

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	free(buffer);

	return (exec);
}
