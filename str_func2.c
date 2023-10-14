#include "shell.h"

/**
 * _puts - prints string
 * @s: string be printed
 * Return: Nothing
 */
void _puts(char *s)
{
	unsigned int i = 0;

	if (!s)
	{
		return;
	}
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _strdup - duplicates a string
 * @s: string be duplicated
 * Return: pointer to duplicated string
 */

char *_strdup(const char *s)
{
	int len = 0;
	char *res;

	if (s == NULL)
	{
		return (NULL);
	}
	while (*s++)
	{
		len++;
	}
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--s;
	return (res);
}

/**
 * _strcpy - copies a string from one to another
 * @destination: destination string
 * @source: source string
 * Return: pointer to destination
 */

char *_strcpy(char *destination, char *source)
{
	unsigned int i = 0;

	if (destination == source || source == 0)
	{
		return (destination);
	}
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * _strncpy - copies a string
 * @destination: destination string
 * @source: source string
 * @n: number of characters be copied
 * Return: pointer to destination string
 */

char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *str = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * _strncat - concatenates 2 strings
 * @destination: 1st string
 * @source: second string
 * @n: number of bytes maximally used
 * Return: concatenated string
 */

char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *str = destination;

	i = 0;
	j = 0;

	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (str);
}
