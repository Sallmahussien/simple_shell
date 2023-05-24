#include "main.h"

/**
 * free_interactive - free buffer, lists
 * @lineptr: buffer from getline
 * @env_list: linked list to the environment variables
*/
void free_interactive(char *lineptr, node *env_list)
{
	free(lineptr);
	free_list(env_list);
}

/**
 * free_noninteractive - free commands, buffer, env_list
 * @commands: array of character pointers to the commands
 * @buffer: buffer from read
 * @env_list: linked-list for the environment variables
*/
void free_noninteractive(char **commands, char *buffer, node *env_list)
{
	free_arr(commands);
	free(buffer);
	free_list(env_list);
}

/**
 * shell_help - helps the interactive, non-interactive, file command func
 * @sequences: array of character pointers to the sequences
 * @lineptr: buffer from read
 * @argv: array of character pointers to arguments from main
 * @envp: array of character pointer to the environment variables from main
 * @exec: pointer to the execute return
 * @env_list: linked list for the environment variables
 * @history: pointer to the history
 * @commands: array of character pointer to sequences
*/
void shell_help(char **sequences, char *lineptr, char **argv, char **envp,
int *exec, node *env_list, int *history, char **commands)
{
	int j, ret, is_builtin;
	char **arr;

	j = 0;
	while (sequences[j])
	{
		arr = parse_string(sequences[j], " ");
		if (arr[0] == NULL)
		{
			free_arr(arr);
			break;
		}
		ret = is_exit(arr, lineptr, argv, exec, env_list, sequences, commands,
		*history);
		if (ret == 1)
		{
			j++;
			continue;
		}
		is_builtin = check_builtins(env_list, arr, exec, argv, *history);
		if (is_builtin)
		{
			j++;
			continue;
		}
		check_command(arr, envp, argv, *history, exec);
		j++;
	}
	free_arr(sequences);
}

/**
 * open_err - generate err message when the file can't be open
 * @argv: array of character pointers to argumnets from main
 * @history: pointer to history
 * @env_list: linked list for environment variables
*/
void open_err(char **argv, int *history, node *env_list)
{
	char *err;

	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	err = tostring(*history);
	write(STDERR_FILENO, err, _strlen(err));
	write(STDERR_FILENO, ": Can't open ", 13);
	write(STDERR_FILENO, argv[1], _strlen(argv[1]));
	write(STDERR_FILENO, "\n", 1);
	free(err);
	free_list(env_list);
}

/**
 * read_from_file - read from file
 * @op: file descriptor of the file
 * @buffer: buffer for storing
 * @env_list: linked list for the environment variables
 * Return: return of read sys call
*/
ssize_t read_from_file(ssize_t op, char *buffer, node *env_list)
{
	ssize_t rd;

	rd = read(op, buffer, 1023);
	if (rd == 0)
	{
		free(buffer);
		free_list(env_list);
		return (rd);
	}
	buffer[rd - 1] = '\0';
	close(op);

	return (rd);
}
