#include "main.h"

/**
 * change_dir - changes the dir to the headed one
 * @dir: directry name
 * @curr_cwd: current cwd
 * @head: head node of linked list
 * Return: 0 or -1
 */

int change_dir(char *dir,  char *curr_cwd, node **head, char **argv, char **arr, int history)
{
	node *env_list;
	char cwd[300], *err;

	env_list = *head;
	if (chdir(dir) == 0)
	{
		set_env("PWD", dir, &env_list, argv, arr, history);
		set_env("OLDPWD", curr_cwd, &env_list, argv, arr, history);
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
		write(STDERR_FILENO, ": can’t cd to ", 16);
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
 * Return: 0 or 2
 */

int change_dir_direct(char *dir, char *curr_cwd, node **head, char **argv, char **arr, int history)
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
 * @dir: the dir that will changed to
 * @value: not used
 * @head: head node of the linked list of the environment
 * Return: 0 on success or 2 on falier
 */

int _cd(char *dir, char *value, node **head, char **argv, char **arr, int history)
{
	char curr_cwd[300];
	node *env_list;
	int ret;

	UNUSED(value);
	env_list = *head;
	if (getcwd(curr_cwd, sizeof(curr_cwd)) == NULL)
	{
		perror("getcwd");
		return (2);
	}

	if (dir == NULL)
		ret = null_dir(curr_cwd, &env_list, argv, arr, history);
	else if (dir[0] == '/')
		ret = change_dir(dir, curr_cwd, &env_list, argv, arr, history);
	else if (_strcmp(dir, "..") == 0)
	{
		if (_strcmp(curr_cwd, "/") == 0)
			return (0);
		ret = back_dir(curr_cwd, &env_list, argv, arr, history);
	}
	else if (_strcmp(dir, "-") == 0)
		ret = past_dir(curr_cwd, &env_list, argv, arr, history);
	else
		ret = change_dir_direct(dir, curr_cwd, &env_list, argv, arr, history);

	return (ret);
}


/**int main(int argc,char **argv)
{
  node *env_list;
  char **env = environ, *arg = NULL;

  env_list = get_env_list(env);

  _cd(argv[1], "whateever", &env_list);
//argv[1] = array[1], whatwever = unused(value)

  free_list(env_list);
  return (0);
}*/
