#include "main.h"

/**
 * interactive - execute shell in the interactive mode
 * @argv: array of pointers to arguments
 * @envp: array of pointers to enviroment variables
 * @env_list: linked list of environment variables
 * Return: the return value of the execution
*/
int interactive(char **argv, char **envp, node *env_list)
{
	ssize_t p;
	size_t n = 0;
	char *lineptr = NULL, **sequences, **commands = NULL;
	int exec, history = 0;

	while (1)
	{
		history++;
		write(STDOUT_FILENO, "$ ", 2);
		p = getline(&lineptr, &n, stdin);
		if (p == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		lineptr[p - 1] = '\0';
		sequences = parse_string(lineptr, ";");
		shell_help(sequences, lineptr, argv, envp, &exec, env_list, &history,
		commands);
	}
	free_interactive(lineptr, env_list);
	return (exec);
}

/**
 * non_interactive - execute shell in the non-interactive mode
 * @argv: array of pointers to arguments
 * @envp: array of character pointers to environment variables
 * @env_list: linked list of environment variables
 * Return: the return value of the execution
*/
int non_interactive(char **argv, char **envp, node *env_list)
{
	char *buffer;
	char **commands, **sequences;
	int exec = 0, i = 0, history = 0;

	buffer = read_for_noninteractive(STDIN_FILENO);
	commands = parse_string(buffer, "\n");
	while (commands[i])
	{
		history++;
		sequences = parse_string(commands[i], ";");
		shell_help(sequences, buffer, argv, envp, &exec, env_list, &history,
		commands);
		i++;
	}
	free_noninteractive(commands, buffer, env_list);
	return (exec);
}

/**
 * file_command - take a file as a command line argument
 * @argv: array of pointers to arguments
 * @envp: array of pointers to enviroment variables
 * @env_list: linked list of environment variables
 * Return: the return value of the execution
 */
int file_command(char **argv, char **envp, node *env_list)
{
	char *buffer, **commands = NULL, **sequences;
	int exec = 0, i = 0, history = 0;
	ssize_t op, rd;

	op = open(argv[1], O_RDONLY);
	if (op == -1)
	{
		open_err(argv, &history, env_list);
		return (127);
	}

	buffer = malloc(sizeof(char) * 1024);
	rd = read_from_file(op, buffer, env_list);
	if (rd == 0)
		return (0);

	commands = parse_string(buffer, "\n");
	while (commands[i])
	{
		history++;
		sequences = parse_string(commands[i], ";");
		shell_help(sequences, buffer, argv, envp, &exec, env_list, &history,
		commands);
		i++;
	}
	free_noninteractive(commands, buffer, env_list);

	return (exec);
}
