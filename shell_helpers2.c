#include "main.h"

/**
 * is_exit - check if the input is "exit or not"
 * @arr: array of parsed strings
 * @argv: argument list that comes from main
 * @lineptr: buffer that be read from getline
 * @ret: the return of the previous process
 * Return: status exit value
*/

int is_exit(char **arr, char *lineptr, char **argv, int ret)
{
	if (_strcmp(arr[0], "exit") == 0 && arr[1] == NULL)
	{
		free_arr(arr);
		free(lineptr);
		exit(ret);
	}
	else if (_strcmp(arr[0], "exit") == 0 && arr[1] != NULL)
	{
		ret = handle_exit_err(arr, argv, lineptr);
	}

	return (ret);
}

/**
 * check_command - check if input is command or not
 * @arr: array of character pointer to parsed string
 * @envp: array of character pointer to environment variables
 * @argv: argument list from main
 * @history: history
 * Return: 0 if the input is not command, 1 if it's command
 */
int check_command(char **arr, char **envp, char **argv, int history)
{
	char *path, **dirs, *arg_path, *err_n;
	int is_dir = 1;

	path = get_path(envp);
	dirs = get_dirs(path);
	arg_path = file_dir(dirs, arr[0]);

	if (!_strcmp(arg_path, "not found"))
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		err_n = tostring(history);
		write(STDERR_FILENO, err_n, _strlen(err_n));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, arr[0], _strlen(arr[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		free(err_n);
		free(arg_path);
		free(path);
		free_arr(arr);
		is_dir = 0;
	}
	else
	{
		if (_strlen(arr[0]) != _strlen(arg_path))
		{
			free(arr[0]);
			arr[0] = malloc(sizeof(char) * (_strlen(arg_path) + 1));
			_strcpy(arr[0], arg_path);
			free(arg_path);
			free(path);
		}
	}
	return (is_dir);
}
