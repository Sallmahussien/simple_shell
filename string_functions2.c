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

	while(str)
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
