#include "shell.h"

/**
 * _putchar - writes character c to stdout
 * @c: character be printed
 * Return: 1 on Success, -1 when Error or otherwise.
 */
int _putchar(char *c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
	{
		buffer[i++] = c;
	}
	return (1);
}

/**
 * _strlen - returns length of a string
 * @str: string
 * Return: length of a string
 */

int _strlen(char *str)
{
	unsigned int i = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - compares 2 strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if str1 == str2, -ve if str1 < str2, +ve if str1 > str2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _starting_with - checks if needle starts with haystack.
 * @haystack: string to be looked for
 * @needle: the substring to find
 * Return: address of next char of haystack, NULL otherwise
 */
char *_starting_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}

/**
 * _strcat - concatenates 2 strings
 * @destination: destination string
 * @source: source string
 * Return: pointer to destination string
 */
char *_strcat(char *destination, char *source)
{
	char *res = destination;

	while (*destination)
	{
		destination++;
	}
	while (*source)
	{
		*destination++ = *source++;
	}
	*destination = *source;
	return (res);
}
