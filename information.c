#include "shell.h"

/**
 * clear_information - clear the info
 *
 * @info: info
 *
 * Return: no
 */

void clear_information(info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_information - set the info
 *
 * @info: info
 * @av: pointer
 *
 * Return: no
 */

void set_information(info *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;
		alias_replace(info);
		vars_replace(info);
	}
}

/**
 * free_information - free the info
 *
 * @info: info
 * @all: int
 *
 * Return: no
 */

void free_information(info *info, int all)
{
	_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		_free(info->environ);
		info->environ = NULL;
		pfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
