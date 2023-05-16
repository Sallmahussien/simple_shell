#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
/*
 * _strlen - Returns the length of a string
 * @s: the string
 * Return: the lenght of the string
 */

int _strlen(char *s)
{
	int i;
	int count = 0;

	for (i = 0; s[i] != '\0'; i++)
		count++;

	return (count);
}

/**
 * *_strcpy - copies thae second string in the first one
 * @dest: first string
 * @src: second string
 * Return: first string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second one
 * @ind: to stop at this index
 * Return: 0 or >0 or <0
 */

int _strcmp(char *s1, char *s2, int ind)
{
	int i;

	for (i = 0 ; i < ind ; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
/**
 * get_path - gets the path of the environment
 * Return: the path
 */

char *get_path(void)
{
	char **curr, *path;
	int len;

	curr = environ;

	while(*curr)
	{
		if ( _strcmp(*curr, "PATH=", 5) == 0)
		{
			len =  _strlen(*curr);
			path = malloc(sizeof(char) * (len + 1));
			if (path == NULL)
				return(NULL);
			_strcpy(path, *curr);
			path[len] = '\0';
			return(path);
		}
		curr++;
	}

	return(NULL);
}

/**
 * get_dirs - toknize the path to directries
 * @path: pointer to the path
 * @return: pointer to array of directries
 */

char **get_dirs(char *path)
{
	char *dir, **dirs;
	int count= 0, i = 0, ii;

	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
      		i++;
	}

	//path[_strlen(path) - 1] = 0;

	dirs = malloc(sizeof(char *) * (count + 2));
	if (dirs == NULL)
		return(NULL);

	i = 0;
	dir = strtok(path, "=");

	do{
		dir = strtok(NULL, ":");
		if (dir == NULL)
			break;
		dirs[i] = malloc(sizeof(char) * (_strlen(dir) + 1));
		if (dirs[i] == NULL)
		{
			for(ii = 0; ii < i; ii++)
				free(dirs[ii]);
			free(dirs);
			return (NULL);
		}

		_strcpy(dirs[i], dir);
		i++;
	}while(dir != NULL);
	dirs[i] = NULL;

	return(dirs);
}


/**
 * file_dir - gets the directery of file
 * @dirs: pointer to array of directries 
 * @char: file name
 * Return: directery
 */

char *file_dir(char **dirs, char *file_name)
{
	char *arg_path, *arg;
	int i = 0, ii, j = 0, len_path = 0, len_arg = 0, flag = 0;


	printf("befor the loop //");

	for(i = 0; file_name[i] != '\0'; i++)
	{
	  printf("inside the loop //");
		if(file_name[i] == '/')
		{
			flag = 1;
			printf("//");
			break;
		}
	  }

	//if(flag == 1 && chdir(file_name) == 0)
	// return (file_name);

	for (i = 0; dirs[i] != NULL; i++)
	{
		if(chdir(dirs[i]) == -1)
		{
			perror("chdir failed");
			continue;
		}
		/**if(flag == 1)
		{
			if(access(file_name, X_OK) == 0)
			{
				for (ii = 0; dirs[ii] != NULL; ii++)
					free(dirs[ii]);
				free(dirs);
				return(file_name);
			}
			}*/
		printf("before if the file name have /");
		if (flag == 1)
		  {
		    printf("in the if ");
		    arg_path = file_name;
		    printf("%s", arg_path);
		  }
		else
		  {
		len_path = _strlen(dirs[i]);
		len_arg = _strlen(file_name);
		arg_path = malloc(sizeof(char) * (len_path + len_arg + 2));
		if (arg_path == NULL)
		{
			for(ii = 0; ii < i; ii++)
				free(dirs[ii]);
			free(dirs);
			free(arg_path);
			return (NULL);
		}
		_strcpy(arg_path, dirs[i]);
		arg_path[len_path] = '/';
		arg = file_name;
		for (j = 0; j < len_arg; j++)
			arg_path[len_path + j + 1] = arg[j];
		arg_path[len_path + j + 1] = '\0';

		if (access(arg_path, X_OK) == 0)
		{
			for (ii = 0; dirs[ii] != NULL; ii++)
				free(dirs[ii]);
			free(dirs);
			return(arg_path);
		}
		  }
		free(arg_path);
	}

	for (ii = 0; dirs[ii] != NULL; ii++)
		free(dirs[ii]);
	free(dirs);

	return(NULL);
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
