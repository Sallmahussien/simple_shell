#include "main.h"

void free_interactive(char *lineptr, node *env_list, ali *list)
{
  free(lineptr);
	free_list(env_list);
	free_ali(list);
}

void free_noninteractive(char **commands, char *buffer, node *env_list)
{
  free_arr(commands);
  free(buffer);
	free_list(env_list);
}
