#include "shell.h"

/**
 * input_buf - buf input
 *
 * @info: info
 * @buf: pointer
 * @len: length
 *
 * Return: sizet
*/

ssize_t input_buf(info *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	ssize_t len_x = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT ,sigintHandler);
#if GETLINE
		x = getline(buf, &len_x, stdin);
#else
		x = _getline(info, buf, &len_x);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			rem_comments(*buf);
			build_history(info, *buf, info->histcount++);
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_ip - input getting
 *
 * @info: info
 *
 * Return: size
*/

ssize_t get_ip(info *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t x = 0;
	char **buf_x = *(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_check(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = NORM;
		}

		*buf_x = p;
		return (_strlen(p));
	}

	*buf_x = buf;
	return (x);
}

/**
 * read_buf - buf reader
 *
 * @info: ionfo
 * @buf: char
 * @i: sizer
 *
 * Return: int
*/

ssize_t read_buf(info *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - getting line
 *
 * @info: info
 * @ptr: pointer
 * @length: length
 *
 * Return: int
*/

int _getline(info *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - handler
 *
 * @sig_num: numvber
 *
 * Return: no
*/

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
