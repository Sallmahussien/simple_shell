#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/**
 * get_path - gets the path of the environment
 * Return: the path
 */

char *get_path(void)
{
	char **curr, *path;
	int len;

	curr = environ;

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
	dir = strtok(path, "=");

	do {
		dir = strtok(NULL, ":");
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
	char *arg_path, *arg;
	int i = 0, ii, j = 0, len_path = 0, len_arg = 0, flag = 0;

	if (file_name[0] == '/')
		flag = 1;
	for (i = 0; dirs[i] != NULL; i++)
	{
		if (chdir(dirs[i]) == -1)
		{
			perror("chdir failed");
			continue;
		}
		if (flag == 1)
		{
			arg_path = malloc(sizeof(char) * strlen(file_name));
			_strcpy(arg_path, file_name);
		}
		else
		{
			len_path = _strlen(dirs[i]);
			len_arg = _strlen(file_name);
			arg_path = malloc(sizeof(char) * (len_path + len_arg + 2));
			if (arg_path == NULL)
			{
				free_dirs(dirs);
				free(arg_path);
				return (NULL);
			}
			_strcpy(arg_path, dirs[i]);
			arg_path[len_path] = '/';
			arg = file_name;
			for (j = 0; j < len_arg; j++)
				arg_path[len_path + j + 1] = arg[j];
			arg_path[len_path + j + 1] = '\0';
		}
		if (access(arg_path, X_OK) == 0)
		{
			free_dirs(dirs);
			return (arg_path);
		}
		free(arg_path);
	}
	free_dirs(dirs);
	return (NULL);
}
/**
 * free_dirs - free array from malloc
 * @dirs: pointer of array of direcertires
 * Return: void
 */

void free_dirs(char **dirs)
{
	for (ii = 0; dirs[ii] != NULL; ii++)
		free(dirs[ii]);
	free(dirs)
}

int main(int argc, char *argv[])
{
	char  *path, *arg_path, **dirs;

	path = get_path();
	dirs = get_dirs(path);
	arg_path = file_dir(dirs, argv[1]);

	printf("%s", arg_path);


	free(arg_path);
	free(path);
	return (0);
}
