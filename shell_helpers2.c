#include "main.h"

/**
 * is_exit - check if the input is "exit or not"
 * @arr: array of parsed strings
 * @argv: argument list that comes from main
 * @lineptr: buffer that be read from getline
 * Return: status exit value
*/

int is_exit(char **arr, char *lineptr, char **argv)
{
	int ret = 0;

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
