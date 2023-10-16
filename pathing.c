#include "shell.h"

/**
 * is_cmd - cmd
 *
 * @info: info
 * @path: char
 *
 * Return: int
*/

int is_cmd(info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_charct - dup the chars
 *
 * @pathstr: char
 * @start: int
 * @stop: int
 *
 * Return: char
*/

char *dup_charct(char *pathstr, int start, int stop)
{
	static char b[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			b[y++] = pathstr[x];
	b[y] = 0;
	return (b);
}

/**
 * find_pathing - find the pathing
 *
 * @info: info
 * @pathstr: char
 * @cmd: char
 *
 * Return: char
*/

char *find_pathing(info *info, char *pathstr, char *cmd)
{
	int i = 0, x = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starting_with(cmd. "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			p = dup_charct(pathstr, x, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[i])
				break;
			x = i;
		}
		i++;
	}
	return (NULL);
}
