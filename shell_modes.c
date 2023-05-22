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
	char *lineptr = NULL, **arr, **sequences;
	int exec, ret = 0, history = 0, is_dir, is_builtin, j;

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
		j = 0;
		while (sequences[j])
		{
			arr = parse_string(sequences[j], " ");

			ret = is_exit(arr, lineptr, argv, ret, env_list, sequences);
			if (ret == -1)
                        	continue;

                	is_builtin = check_builtins(env_list, arr, &ret);
                	if (is_builtin)
			{
				j++;
                        	continue;
			}

                	is_dir = check_command(arr, envp, argv, history);
                	if (!is_dir)
                	{
                        	ret = 127;
				j++;
                        	continue;
                	}

                	exec = execute(arr, argv);

                	ret = exec;
                	free_arr(arr);
			j++;
		}
		free_arr(sequences);
	}

	free(lineptr);
	free_list(env_list);

	return (ret);
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
	char **arr, **commands, **sequences;
	int exec = 0, i = 0, ret = 0, history = 0, is_dir, is_builtin, j;

	buffer = read_for_noninteractive(STDIN_FILENO);
	commands = parse_string(buffer, "\n");

	while(commands[i])
	{
		history++;

		sequences = parse_string(commands[i], ";");
		j = 0;
		while (sequences[j])
		{
			arr = parse_string(sequences[j], " ");
			ret = is_exit(arr, buffer, argv, ret, env_list, sequences);
			if (ret == -1)
				continue;
			is_builtin = check_builtins(env_list, arr, &ret);
			if (is_builtin)
			{
				j++;
				continue;
			}
			is_dir = check_command(arr, envp, argv, history);
			if (!is_dir)
			{
				ret = 127;
				j++;
				continue;
			}
			exec = execute(arr, argv);
			free_arr(arr);
			j++;
		}
		i++;
		free_arr(sequences);
	}
	free_arr(commands);
	free(buffer);
	free_list(env_list);

	return (exec);
}

/**
 * file_command: take a file as a command line argument
 * @argv: array of pointers to arguments
 * @envp: array of pointers to enviroment variables
 * @env_list: linked list of environment variables
 * Return: the return value of the execution
 */
int file_command(char **argv, char **envp, node *env_list)
{
	char *buffer, **arr, **commands, *err, **sequences;
	int exec = 0, i = 0, ret = 0, history = 0, is_dir, is_builtin, j;
	ssize_t op, rd;

	UNUSED(sequences);


	op = open(argv[1], O_RDONLY);
	if (op == -1)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": ", 2);
		err = tostring(history);
		write(STDERR_FILENO, err, _strlen(err));
		write(STDERR_FILENO, ": Can't open ", 13);
		write(STDERR_FILENO, argv[1], _strlen(argv[1]));
		write(STDERR_FILENO, "\n", 1);
		free(err);
		return (127);
	}
	
	buffer = malloc(sizeof(char) * 1024);
	rd = read(op, buffer, 1023);
	if (rd == -1)
		return (-1);
	buffer[rd - 1] = '\0';
	close (op);

	commands = parse_string(buffer, "\n");

	while(commands[i])
	{
		history++;
		sequences = parse_string(commands[i], ";");
		j = 0;
		while (sequences[j])
		{
			arr = parse_string(sequences[j], " ");

			ret = is_exit(arr, buffer, argv, ret, env_list, sequences);
			if (ret == -1)
				continue;
			is_builtin = check_builtins(env_list, arr, &ret);
			if (is_builtin)
			{
				j++;
				continue;
			}
			is_dir = check_command(arr, envp, argv, history);
			if (!is_dir)
			{
				ret = 127;
				j++;
				continue;
			}
			exec = execute(arr, argv);
			free_arr(arr);
			j++;

		}
		i++;
		free_arr(sequences);
	}
	free_arr(commands);
	free(buffer);
	free_list(env_list);

	return (exec);
}
