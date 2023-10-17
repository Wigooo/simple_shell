#include "shell.h"

/**
 * my_history - displays history list
 * @information: structure containing potential of args
 * Return: 0
 */
int my_history(info *information)
{
	print_ls(information->history);
	return (0);
}

/**
 * alias_unset - unsets alias to a str
 * @information: structure containing potential of args
 * @s: string alias
 * Return: 0 on success, 1 if fail
 */
int alias_unset(info *information, char *s)
{
	char *ptr, ch;
	int res;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	res = delete_node(&(information->alias),
			getting_node_idx(information->alias,
				starting_with_node(information->alias, s, -1)));
	*ptr = ch;
	return (res);
}

/**
 * alias_set - sets alias to string
 * @information: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info *information, char *s)
{
	char *ptr;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (alias_unset(information, s));

	alias_unset(information, s);
	return (node_end(&(information->alias), s, 0) == NULL);
}

/**
 * alias_print - prints  alias string
 * @n: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(lists *n)
{
	char *ptr = NULL, *a = NULL;

	if (n)
	{
		ptr = _strchr(n->str, '=');
		for (a = n->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * own_alias - emulates the alias builtin (man alias)
 * @information: Structure containing potential of args.
 *  Return: Always 0
 */
int own_alias(info *information)
{
	int i = 0;
	char *ptr = NULL;
	lists *n = NULL;

	if (information->argc == 1)
	{
		n = information->alias;
		while (n)
		{
			alias_print(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; information->argv[i]; i++)
	{
		ptr = _strchr(information->argv[i], '=');
		if (ptr)
			alias_set(information, information->argv[i]);
		else
			alias_print(starting_with_node(information->alias,
						information->argv[i], '='));
	}

	return (0);
}
