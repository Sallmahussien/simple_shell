#include "main.h"

/**
 * main - Entry point
 * @argc: no. of arguments
 * @argv: list of arguments
 * @envp: environment
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	int ret;
	node *env_list;

	env_list = get_env_list(envp);

	if (argc != 1)
	{
		ret = file_command(argv, envp, env_list);
		return (ret);
	}

	if (isatty(STDIN_FILENO))
		ret = interactive(argv, envp, env_list);
	else
		ret = non_interactive(argv, envp, env_list);

	return (ret);
}
