#include "main.h"

/**
 * interactive - execute shell in the interactive mode
 * @argv: array of pointers to arguments
 * @envp: array of pointers to enviroment variables
 * Return: the return value of the execution
*/
int interactive(char **argv, char **envp)
{
	ssize_t p;
	size_t n = 0;
	char *lineptr = NULL, **arr;
	int exec, ret = 0, history = 0, is_dir;

	while (1)
	{
		history++;
		write(STDOUT_FILENO, "$ ", 2);

		p = getline(&lineptr, &n, stdin);
		if (p == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		lineptr[p - 1] = '\0';

		arr = parse_string(lineptr, " ");

		ret = is_exit(arr, lineptr, argv, ret);
		if (ret == -1)
			continue;

		is_dir = check_command(arr, envp, argv, history);
		if (!is_dir)
		{
			ret = 127;
			continue;
		}

		exec = execute(arr, argv);

		ret = exec;
		free_arr(arr);
	}

	free(lineptr);

	return (ret);
}

/**
 * non_interactive - execute shell in the non-interactive mode
 * @argv: array of pointers to arguments
 * Return: the return value of the execution
*/
int non_interactive(char **argv, char **envp)
{
	char *buffer;
	char **arr, **comands;
	int exec = 0, i = 0, ret = 0, history = 0, is_dir;

	buffer = read_for_noninteractive();
	comands = parse_string(buffer, "\n");

	while(comands[i])
	{
		history++;

		arr = parse_string(comands[i], " ");

		ret = is_exit(arr, comands[i], argv, ret);
			if (ret == -1)
				return (exec);
		is_dir = check_command(arr, envp, argv, history);
		if (!is_dir)
		{
			ret = 127;
			return (ret);
		}

		exec = execute(arr, argv);

		free_arr(arr);
		i++;
	}
	free(buffer);

	return (exec);
}
