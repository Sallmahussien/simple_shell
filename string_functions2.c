#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The integer value of the converted string.
 */
int _atoi(char *str)
{
	int sign = 1;
	unsigned int num = 0;

	while (str)
	{
		if (*str == '-')
			sign *= -1;

		else if (*str >= '0' && *str <= '9')
			num = (num * 10) + (*str - '0');

		else
			break;

		str++;
	}

	return (num * sign);
}

/**
 * tostring - converts number to string
 * @num: input num
 * Return: string
*/
char *tostring(int num)
{
	int n, len = 0, i;
	char *str;

	if (num == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = num + '0';
		str[1] = '\0';
		return (str);
	}

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}

	str = malloc(sizeof(char) * (len + 1));

	for (i = 0; i < len; i++)
	{
		str[len - i - 1] = (num % 10) + '0';
		num /= 10;
	}

	str[i] = '\0';

	return (str);
}

/**
 * _strdup - dupplicate the string
 * @str: string
 * Return: string
 */

char *_strdup(char *str)
{
	int i, ii, len = 0;
	char *dup;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		len++;
	dup = (char *) malloc(len + 1 * sizeof(char));
	if (dup == NULL)
		return (NULL);
	for (ii = 0; ii < len; ii++)
		dup[ii] = str[ii];
	dup[ii] = '\0';
	return (dup);
}

/**
 * strnum - return number of strings in array of strings
 * @arr: array of pointer to strings
 * Return: no of strings
 */
int strnum(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
		;

	return (i);
}
