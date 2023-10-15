#include "shell.h"

/**
 * get_history - get the history
 *
 * @info: info
 *
 * Return: char
*/

char *get_history(info *info)
{
	char *x, *y;

	y = _getenv(info, "HOME=");
	if (!y)
		return (NULL);
	x = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_F) + 2));
	if (!x)
		return (NULL);
	x[0] = 0;
	_strcpy(x, y);
	_strcat(x, "/");
	_strcat(x, HIST_F);
	return (x);
}

/**
 * history_write - write the history
 *
 * @info: info
 *
 * Return: int
*/

int history_write(info *info)
{
	ssize_t x;
	char *f = get_history(info);
	list *n = NULL;

	if (!f)
		return (-1);

	x = open(f, 0_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f);
	if (x == -1)
		return (-1);
	for (n = info->history; n = n->next)
	{
		_putsfd(n->str, x);
		_putfd('\n', x);
	}
	_putfd(BUFFER_FLUSH, x);
	close(x);
	return (1);
}

/**
 * history_read - read the histpru
 *
 * @info: info
 *
 * Return: int
*/

int history_read(info *info)
{
	int i, l, line = 0;
	ssize_t x, rd, s = 0;
	struct stat st;
	char *b = NULL, *f = get_history(info);

	if (!f)
		return (0);

	x = open(f, O_RDONLY);
	free(f);
	if (x == -1)
		return (0);
	if (!fstat(x, &st))
		s  = st.st_size;
	if (s < 2)
		return (0);
	b = malloc(sizeof(char) * (s + 1));
	if (!b)
		return (0);
	rd = read(x, b, s);
	b[s] = 0;
	if (rd <= 0)
		return (free(b), 0);
	close(x);
	for (i = 0; i < s; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			build_history(info, b + l, line++);
			l = i + 1;
		}
	if (l != i)
		build_history(info, b + l, line++);
	free(b);
	info->histcount = line;
	while (info->histcount-- >= HIST_M)
		delete_node(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history - build the history
 *
 * @info: info
 * @buf: char
 * @linecount: int
 *
 * Return: int
*/

int build_history(info *info, char *buf, int linecount)
{
	list *n = NULL;

	if (info->history)
		n = info->linecount;

	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumber_history - renumber it
 *
 * @info: info
 *
 * Return: int
*/

int renumber_history(info *info)
{
	list *n = info->history;
	int x = 0;

	while (n)
	{
		n->num = x++;
		n = n->next;
	}
	return (info->histcount = x);
}
