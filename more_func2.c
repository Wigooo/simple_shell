#include "shell.h"

/**
 * _erroratoi - converts a string to an integer
 * @str: string be converted
 * Return: 0 if no numbers, converted number otherwise, -1 on error
 */
int _erroratoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '\0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * rem_comments - function replaces 1st instances of '#' with '\0'
 * @buffer: address of string be modified
 * Return: 0
 */
void rem_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '0';
			break;
		}
}

/**
 * print_err - printing error message
 * @info: parameter returned and info struct
 * @err_str: string containing specified error type
 * Return: 0 if no numbers, converted number if success, -1 on error
 */
void print_err(info *info, char *err_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(err_str);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @in_put: input
 * @fd: fielddescriptor
 * Return: number of chars printed
 */
int print_decimal(int in_put, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, counter = 0;
	unsigned int _abs_, present;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (in_put < 0)
	{
		_abs_ = -in_put;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = in_put;
	present = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + present / i);
			counter++;
		}
		present %= i;
	}
	__putchar('0' + present);
	counter++;

	return (counter);
}
