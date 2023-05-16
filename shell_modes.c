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
	int i, exec;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		p = getline(&lineptr, &n, stdin);
		if (p == -1)
			break;

		lineptr[p - 1] = '\0';

		arr = parse_string(lineptr);

		exec = execute(arr, argv);

		for (i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}

	free(lineptr);

	return (exec);
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
	int exec, i;

	buffer = read_for_noninteractive();

	arr = parse_string(buffer);

	exec = execute(arr, argv);

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	free(buffer);

	return (exec);
}
