#include "main.h"

/**
 * parse_string - parse a string according to a delimiter
 * @lineptr: input string
 * @delim: delimeter
 * Return: array of pointer characters to the parsed string
*/

char **parse_string(char *lineptr, char *delim)
{
	char *token, *input, *cpy_input;
	char **arg;
	int no_tokens = 0, i = 0;

	input = malloc(sizeof(char) * (_strlen(lineptr) + 1));
	_strcpy(input, lineptr);

	cpy_input = malloc(sizeof(char) * (_strlen(lineptr) + 1));
	_strcpy(cpy_input, input);

	token = _strtok(input, delim);
	while (token != NULL)
	{
		no_tokens++;
		token = _strtok(NULL, delim);
	}

	arg = malloc(sizeof(char *) * (no_tokens + 1));

	token = _strtok(cpy_input, delim);
	while (token)
	{
		arg[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(arg[i++], token);
		token = _strtok(NULL, delim);
	}
	arg[i] = NULL;

	free(input);
	free(cpy_input);

	return (arg);
}

/**
 * execute - execute the command with arguments
 * @args: array to character pointers to command and argument
 * @argv: array of pointers to arguments from main func
 * @history: history
 * @arg_path: path
 * @envp: environment
 * Return: -1 on error and 0 on sucess
*/
int execute(char **args, char **argv, int history, char *arg_path, char **envp)
{
	pid_t pid;
	int exec = 0, status;
	char *err;

	pid = fork();
		if (pid == -1)
		{
			perror(argv[0]);
			return (-1);
		}
		else if (pid == 0)
		{
			if (execve(arg_path, args, envp) == -1)
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				write(STDERR_FILENO, ": ", 2);
				err = tostring(history);
				write(STDERR_FILENO, err, _strlen(err));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, args[1], _strlen(args[1]));
				write(STDERR_FILENO, ": Permission denied\n", 21);
				free(err);
				exec = 126;
				_exit(exec);
			}
		}
		else
		{
			wait(&status);
			exec = WEXITSTATUS(status);
		}
		return (exec);
}

/**
 * read_for_noninteractive - read the input for non-interactive mode
 * @fd: file descriptor
 * Return: pointer to buffer that has the input
*/
char *read_for_noninteractive(ssize_t fd)
{
	char *buffer;
	int rd;

	buffer = malloc(sizeof(char) * 1024);
	rd = read(fd, buffer, 1023);

	buffer[rd - 1] = '\0';
	return (buffer);
}

/**
 * handle_exit_err - handle errors for exit built-in
 * @arr: array of parsed strings
 * @argv: argument list that comes from main
 * @lineptr: buffer that be read from getline
 * @env_list: linked list for environment variables
 * @sequences: array of pointers to sequences commands
 *  @exec: the return of the previous process
 * @commands: array to pointers to commands
 * @history: history
 * Return: return value of exit
*/

int handle_exit_err(char **arr, char **argv, char *lineptr, node *env_list,
		char **sequences, int *exec, char **commands, int history)
{
	int ret = 0, num = _atoi(arr[1]);
	char *err = NULL;

	while (num > 255)
		num -= 256;

	if ((arr[1][0] - '0' == 0 || num > 0) && num <= 255)
	{
		ret = num;
		free_arr(arr);
		free(lineptr);
		free_list(env_list);
		free_arr(sequences);
		free_arr(commands);
		exit(ret);
	}
	else if (_atoi(arr[1]) <= 0)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		err = tostring(history);
		write(STDERR_FILENO, err, _strlen(err));
		write(STDERR_FILENO, ": exit: Illegal number: ", 24);
		write(STDERR_FILENO, arr[1], _strlen(arr[1]));
		write(STDERR_FILENO, "\n", 1);
		*exec = 2;
		ret = 1;
		free(err);
		free_arr(arr);
	}

	return (ret);
}
