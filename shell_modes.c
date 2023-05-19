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
	char *lineptr = NULL, **arr;
	char *path, *arg_path, **dirs, *err, *err_n;
	int exec, ret = 0, history = 1;
	/*int i = 0;*/

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

		ret = is_exit(arr, lineptr, argv, ret);
		if (ret == -1)
			continue;

		path = get_path();
		dirs = get_dirs(path);
		arg_path = file_dir(dirs, arr[0]);

		if (!_strcmp(arg_path, "not found"))
		{
			err = malloc(sizeof(char) * (_strlen(argv[0]) + _strlen(arr[0]) + 16));
			_strcpy(err, argv[0]);
			_strcat(err, ": ");
			err_n = tostring(history);
			_strcat(err, err_n);
			_strcat(err, ": ");
			_strcat(err, arr[0]);
			_strcat(err, ": not found\n");
			ret = 127;
			write(STDERR_FILENO, err, _strlen(err));
			free(err);
			free(err_n);
			continue;
		}
		else
		{
			arr[0] = _realloc(arr[0], _strlen(arr[0]), _strlen(arg_path));
			strcpy(arr[0], arg_path);
		}

		exec = execute(arr, argv);

		ret = exec;
		free(arg_path);
		free(path);
		free_arr(arr);
		history++;
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
	int exec = 0, i, ret = 0;

	buffer = read_for_noninteractive();

	arr = parse_string(buffer);

	ret = is_exit(arr, buffer, argv, ret);
		if (ret == -1)
			return (exec);

	exec = execute(arr, argv);

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	free(buffer);

	return (exec);
}
