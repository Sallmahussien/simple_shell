#include "main.h"

/**
 * change_dir - changes the dir to the headed one
 * @dir: directry name
 * @curr_cwd: current cwd
 * @head: head node of linked list
 * @argv: array of character pointer to argumnets from main
 * @arr: arry of character pointer to parsed string
 * @history: history
 * Return: 0 or -1
 */

int change_dir(char *dir,  char *curr_cwd, node **head,
	       char **argv, char **arr, int history)
{
	node *env_list;
	char cwd[300], *err;
	char *arr_pwd[4] = {"set_env", "PWD"}, *arr_old[4] = {"set_env", "OLDPWD"};

	arr_pwd[2] = dir;
	arr_pwd[3] = NULL;
	arr_old[2] = curr_cwd;
	arr_old[3] = NULL;
	env_list = *head;
	if (chdir(dir) == 0)
	{
		set_env(&env_list, argv, arr_pwd, history);
		set_env(&env_list, argv, arr_old, history);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return (2);
		}
		return (0);
	}
	else
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		err = tostring(history);
		write(STDERR_FILENO, err, _strlen(err));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, arr[0], _strlen(arr[0]));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, arr[1], _strlen(arr[1]));
		write(STDERR_FILENO, "\n", 1);
		free(err);

		return (2);
	}
}

/**
 * change_dir_direct - changes the dir to directry in the current cwd
 * @dir: directry name
 * @curr_cwd: current cwd
 * @head: head node of linked list
 * @argv: array of character pointer to argumnets from main
 * @arr: arry of character pointer to parsed string
 * @history: history
 * Return: 0 or 2
 */

int change_dir_direct(char *dir, char *curr_cwd, node **head,
		      char **argv, char **arr, int history)
{
	node *env_list = *head;
	char *new_dir;

	new_dir = malloc(sizeof(char) * (_strlen(curr_cwd) + _strlen(dir) + 2));
	if (new_dir == NULL)
	{
		perror("malloc");
		return (2);
	}
	_strcpy(new_dir, curr_cwd);
	_strcat(new_dir, "/");
	_strcat(new_dir, dir);
	new_dir[_strlen(new_dir)] = '\0';

	if (change_dir(new_dir, curr_cwd, &env_list, argv, arr, history) == 0)
	{
		free(new_dir);
		return (0);
	}
	else
	{
		free(new_dir);
		return (2);
	}
}


/**
 * _cd - Changes the current directory of the process.
 * @head: head node of the linked list of the environment
 * @argv: array of character pointer to argumnets from main
 * @arr: arry of character pointer to parsed string
 * @history: history
 * Return: 0 on success or 2 on falier
 */

int _cd(node **head, char **argv, char **arr, int history)
{
	char curr_cwd[300];
	node *env_list;
	int ret;

	env_list = *head;
	if (getcwd(curr_cwd, sizeof(curr_cwd)) == NULL)
	{
		perror("getcwd");
		return (2);
	}

	if (arr[1] == NULL || _strcmp(arr[1], "~") == 0)
		ret = null_dir(curr_cwd, &env_list, argv, arr, history);
	else if (arr[1][0] == '/')
		ret = change_dir(arr[1], curr_cwd, &env_list, argv, arr, history);
	else if (_strcmp(arr[1], "..") == 0)
	{
		if (_strcmp(curr_cwd, "/") == 0)
			return (0);
		ret = back_dir(curr_cwd, &env_list, argv, arr, history);
	}
	else if (_strcmp(arr[1], "-") == 0)
		ret = past_dir(curr_cwd, &env_list, argv, arr, history);
	else
		ret = change_dir_direct(arr[1], curr_cwd, &env_list, argv, arr, history);

	return (ret);
}
