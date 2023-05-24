#include "main.h"

/**
 * _strtok - breaks a string into tokens
 * @str: input string to be breaked
 * @delim: delimeter that used to break string at
 * Return: pointer to tokens
*/

char *_strtok(char *str, char *delim)
{
	static char *ptr;
	char *token;

	if (str != NULL)
		ptr = str;

	while (!_strncmp(ptr, delim, _strlen(delim)))
		ptr += _strlen(delim);

	if (ptr == NULL || *ptr == '\0')
		return (NULL);

	token = ptr;
	while (*ptr != '\0')
	{
		if (*ptr == *delim)
		{
			*ptr = '\0';
			ptr++;
			break;
		}
		ptr++;
	}

	return (token);
}
