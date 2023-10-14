#include "shell.h"

/**
 * _strchr - locates a character in a string
 * @str: string be looked in
 * @c: character be located
 * Return: pointer to memo area
 */

char *_strchr(char *str, char *c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}

/**
 * **strtow - splits a string to words, ignore repeated delemiters
 * @str: input string
 * @del: delimeter
 * Return: pointer to array of strings, NULL if failure
 */
char **strtow(char *str, char del)
{
	int x, y, z, j, words_number = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";

	for (x = 0; str[x] != '\0'; x++)
	{
		if (!is_delimeter(str[x], del) &&
				(is_delimeter(str[x + 1], del) || !str[x + 1]))
			words_number++;
	}
	if (words_number == 0)
		return (NULL);
	s = malloc((1 + words_number) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < words_number; y++)
	{
		while (is_delimeter(str[x], del))
			x++;
		z = 0;
		while (!is_delimeter(str[x + z], del) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (j = 0; j < z; j++)
			s[y][j] = str[x++];
		s[y][j] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string to words
 * @str: input string
 * @del: delimeter
 * Return: pointer to array of strings, NULL if failure
 */

char **strtow2(char *str, char del)
{
	int x, y, z, j, words_number = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
	{
		if ((str[x] != del && str[x + 1] == del) ||
				(str[x] != del && !str[x + 1]) || str[x + 1] == del)
			words_number++;
	}
	if (words_number == 0)
		return (NULL);
	s = malloc((1 + words_number) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < words_number; y++)
	{
		while (str[x] == del && str[x] != del)
			x++;
		z = 0;
		while (str[x + z] != del && str[x + z] && str[x + z] != del)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (j = 0; j < z; j++)
			s[y][j] = str[x++];
		s[y][j] = 0;
	}
	s[y] = NULL;
	return (s);
}
