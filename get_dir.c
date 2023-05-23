#include "main.h"

/**
 * get_path - gets the path of the environment
 * @envp: enviroment variable
 * Return: the path
 */

char *get_path(char **envp)
{
	char **curr, *path;
	int len;

	curr = envp;

	while (*curr)
	{
		if (_strncmp(*curr, "PATH=", 5) == 0)
		{
			len =  _strlen(*curr);
			path = malloc(sizeof(char) * (len + 1));
			if (path == NULL)
				return (NULL);
			_strcpy(path, *curr);
			path[len] = '\0';
			return (path);
		}
		curr++;
	}

	return (NULL);
}

/**
 * get_dirs - toknize the path to directries
 * @path: pointer to the path
 * Return: pointer to array of directries
 */

char **get_dirs(char *path)
{
	char *dir, **dirs;
	int count = 0, i = 0, ii;

	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}

	dirs = malloc(sizeof(char *) * (count + 2));
	if (dirs == NULL)
		return (NULL);

	i = 0;
	dir = _strtok(path, "=");

	do {
		dir = _strtok(NULL, ":");
		if (dir == NULL)
			break;
		dirs[i] = malloc(sizeof(char) * (_strlen(dir) + 1));
		if (dirs[i] == NULL)
		{
			for (ii = 0; ii < i; ii++)
				free(dirs[ii]);
			free(dirs);
			return (NULL);
		}

		_strcpy(dirs[i], dir);
		i++;
	} while (dir != NULL);
	dirs[i] = NULL;

	return (dirs);
}


/**
 * file_dir - gets the directery of file
 * @dirs: pointer to array of directries
 * @file_name: file name
 * Return: directery
 */

char *file_dir(char **dirs, char *file_name)
{
	char *arg_path;
	int i = 0, len_path = 0, len_arg = 0, flag = 0;

	flag = (file_name[0] == '/') ? 1 : 0;
	for (i = 0; dirs[i] != NULL; i++)
	{
		if (flag == 1)
		{
			arg_path = malloc(sizeof(char) * (strlen(file_name) + 1));
			_strcpy(arg_path, file_name);
		}
		else
		{
			len_path = _strlen(dirs[i]);
			len_arg = _strlen(file_name);
			arg_path = malloc(sizeof(char) * (len_path + len_arg + 2));
			if (arg_path == NULL)
			{
				free_arr(dirs);
				free(arg_path);
				return (NULL);
			}
			_strcpy(arg_path, dirs[i]);
			_strcat(arg_path, "/");
			_strcat(arg_path, file_name);
		}
		if (access(arg_path, X_OK) == 0)
		{
			free_arr(dirs);
			return (arg_path);
		}
		free(arg_path);
	}
	arg_path = malloc(sizeof(char) * 10);
	_strcpy(arg_path, "not found");
	free_arr(dirs);
	return (arg_path);
}
/**
 * free_arr - free array from malloc
 * @arr: pointer of array of direcertires
 * Return: void
 */

void free_arr(char **arr)
{
	int ii;

	for (ii = 0; arr[ii] != NULL; ii++)
		free(arr[ii]);
	free(arr);
}
