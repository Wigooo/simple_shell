#include "shell.h"

/**
 * _interact - returns true if shell in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int _interact(info *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @c: character be checked
 * @delimeter: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char c, char *delimeter)
{
	while (*delimeter)
	{
		if (*delimeter++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checking if alphabetic character
 * @c: input character
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to integer
 * @str: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, out_put;
	unsigned int res = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		out_put = -res;
	else
		out_put = res;
	return (out_put);
}

/**
 * number_convert - function to convert, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *number_convert(long int number, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *pointer;
	unsigned long n = number;

	if (!(flags & UNSIGNED_CONVERT) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	arr = flags & LOWERCASE_CONVERT ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buff[49];
	*pointer = '\0';

	do {
		*--pointer = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}
