#include "main.h"

/**
 * main - Entry point
 * @argc: no. of arguments
 * @argv: list of arguments
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
		char **envp __attribute__((unused)))
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
