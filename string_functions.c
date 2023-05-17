#include "main.h"

/**
 * _strlen - Returns the length of a string
 * @s: the string
 * Return: the lenght of the string
 */

int _strlen(char *s)
{
	int i;
	int count = 0;

	for (i = 0; s[i] != '\0'; i++)
		count++;

	return (count);
}

/**
 * *_strcpy - copies thae second string in the first one
 * @dest: first string
 * @src: second string
 * Return: first string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strncmp - compares two strings
 * @s1: first string
 * @s2: second one
 * @ind: to stop at this index
 * Return: 0 or >0 or <0
 */

int _strncmp(char *s1, char *s2, int ind)
{
	int i;

	for (i = 0 ; i < ind ; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second one
 * Return: 0 or >0 or <0
 */

int _strcmp(char *s1, char *s2)
{
	int i;
	int len = 0;
	int len2 = 0;

	for (i = 0; s1[i] != '\0'; i++)
		len++;
	for (i = 0; s2[i] != '\0'; i++)
		len2++;
	for (i = 0 ; i < len || i < len2; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * *_strcat - concatinate two strings
 * @dest: first string
 * @src: second one
 * Return: the new string
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int len = 0;
	int len2 = 0;

        len = _strlen(dest);
        len2 = _strlen(src);
	for (i = 0; i < len2; i++)
		dest[len++] = src[i];
	return (dest);
}
