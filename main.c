#include "main.h"

/**
 * main - Entry point
 * @argc: no. of arguments
 * @argv: list of arguments
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	int ret;

	if (isatty(STDIN_FILENO))
		ret = interactive(argv);
	else
		ret = non_interactive(argv);

	return (ret);
}
