#include "main.h"

/**
 * is_exit - check if the input is "exit or not"
 * @arr: array of parsed strings
 * @lineptr: buffer that be read from getline
 * @argv: argument list that comes from main
 * @exec: the return of the previous process
 * @env_list: linked list for environment variables
 * @sequences: array to pointers to sequencing commands
 * @commands: array to pointers to commands
 * @history: history
 * Return: status exit value
*/
int is_exit(char **arr, char *lineptr, char **argv, int *exec, node *env_list,
		char **sequences, char **commands, int history)
{
	int ret = 0;

	if (_strcmp(arr[0], "exit") == 0 && arr[1] == NULL)
	{
		free_arr(arr);
		free(lineptr);
		free_list(env_list);
		free_arr(sequences);
		free_arr(commands);
		exit(*exec);
	}
	else if (_strcmp(arr[0], "exit") == 0 && arr[1] != NULL)
	{
		ret = handle_exit_err(arr, argv, lineptr, env_list, sequences, exec,
		commands, history);
	}

	return (ret);
}

/**
 * check_command - check if input is command or not
 * @arr: array of character pointer to parsed string
 * @envp: array of character pointer to environment variables
 * @argv: argument list from main
 * @history: history
 * @exec: pointer for the return value from execute
 * Return: 0 if the input is not command, 1 if it's command
 */
int check_command(char **arr, char **envp, char **argv, int history, int *exec)
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
		free_arr(arr);
		free(path);
		*exec = 127;
		is_dir = 0;
	}
	else
	{
		*exec = execute(arr, argv, history, arg_path, envp);
		free_arr(arr);
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
 * @argv: array of character pointers to argumnets from main
 * @history: history
 * Return: 0 if the command is not built-in, 1 otherwise
 */
int check_builtins(node *env_list, char **arr, int *ret, char **argv,
		int history)
{
	int is_builtin = 0, i;
	builtin my_builtins[] = {
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", _cd},
		{NULL, NULL}
	};

	for (i = 0; my_builtins[i].command; i++)
	{
		if (!_strcmp(my_builtins[i].command, arr[0]))
		{
			*ret = my_builtins[i].func(&env_list, argv, arr, history);
			break;
		}
	}
	check_null(my_builtins[i].command, arr, &is_builtin);
	return (is_builtin);
}

/**
 * check_null - check if the commd is null or not
 * @command: command
 * @arr: array of character pointer to parsed string
 * @is_builtin: builtin command or not
 */
void check_null(char *command, char **arr, int *is_builtin)
{
	if (command)
	{
		free_arr(arr);
		*is_builtin = 1;
	}
}
