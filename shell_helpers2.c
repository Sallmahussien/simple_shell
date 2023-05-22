#include "main.h"

/**
 * is_exit - check if the input is "exit or not"
 * @arr: array of parsed strings
 * @argv: argument list that comes from main
 * @lineptr: buffer that be read from getline
 * @ret: the return of the previous process
 * @env_list: linked list for environment variables
 * @sequences: array to pointers to sequencing commands
 * Return: status exit value
*/

int is_exit(char **arr, char *lineptr, char **argv, int ret, node *env_list, char **sequences)
{
	if (_strcmp(arr[0], "exit") == 0 && arr[1] == NULL)
	{
		free_arr(arr);
		free(lineptr);
		free_list(env_list);
		free_arr(sequences);
		exit(ret);
	}
	else if (_strcmp(arr[0], "exit") == 0 && arr[1] != NULL)
	{
		ret = handle_exit_err(arr, argv, lineptr, env_list, sequences);
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
		}
		free(arg_path);
		free(path);
	}
	return (is_dir);
}

/**
 * check_builtins - check if the command is built-in or not
 * @env_list: linked list of environment variables
 * @arr: array of character pointers to patsed strings
 * @ret: pointer to the return value
 * Return: 0 if the command is not built-in, 1 otherwise
 */
int check_builtins(node *env_list, char **arr, int *ret)
{
	int is_builtin = 0, i;
	builtin my_builtins[] = {
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};

	for (i = 0; my_builtins[i].command; i++)
	{
		if (!_strcmp(arr[0], "env") && !_strcmp(my_builtins[i].command, arr[0]))
		{
			*ret = my_builtins[i].func(arr[0], NULL, &env_list);
			break;
		}
		if (!_strcmp(arr[0], "setenv") && !_strcmp(my_builtins[i].command, arr[0]))
		{
			if (strnum(arr) != 3)
			{
				write(STDERR_FILENO, "usage: setenv var value\n", 25);
				break;
			}
			*ret = my_builtins[i].func(arr[1], arr[2], &env_list);
			break;
		}
		if (!_strcmp(my_builtins[i].command, arr[0])) 
		{
			if (strnum(arr) != 2)
			{
				write(STDERR_FILENO, "usage: unsetenv var\n", 21);
				break;
			}
			*ret = my_builtins[i].func(arr[1], arr[2], &env_list);
			break;
		}		
	}
	check_null(my_builtins[i].command, arr, &is_builtin);
	return (is_builtin);
}
void check_null(char *command, char **arr, int *is_builtin)
{
	if (command)
	{
		free_arr(arr);
		*is_builtin = 1;
	}
}
