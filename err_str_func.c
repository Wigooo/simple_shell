#include "shell.h"

/**
 * _errputchar - writes char c to stderr
 * @c: character to printed
 * Return: 1 on success, -1 on error and err number is set
 */
int _errputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _errputs - printing input string
 * @str: string be printed
 * Return: nothing
 */
void _errputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errputchar(str[i]);
		i++;
	}
}

/**
 * _putfd - writes c character to fd
 * @c: character printed
 * @fd: fileddescriptor
 * Return: 1 if success, -1 if error and errno. is set
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _putsfd - prints string
 * @str: string be printed
 * @fd: fileddescriptor
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
