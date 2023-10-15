#include "shell.h"

/**
 * current_env - prints current enviroment
 * @information: structure containing potential args,
 *                  to maintain const func prototype.
 * Return: 0
 */
int current_env(info *information)
{
	print_list(information->env);
	return (0);
}

/**
 * get_env - gets value of required variable
 * @information: structure containing potential args
 * @var: env variable name
 * Return: value
 */
char *get_env(info *information, const char *var)
{
	lists *n = information->env;
	char *ptr;

	while (n)
	{
		ptr = _starting_with(n->str, var);
		if (ptr && *ptr)
			return (ptr);
		n = n->next;
	}
	return (NULL);
}

/**
 * myset_env - changes or add a enviroment variable
 * @information: structure containing potential args
 * Return: 0
 */
int myset_env(info *information)
{
	if (information->argc != 3)
	{
		_errputs("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * myunset_env - removes env variable
 * @information: structure containing potential args
 * Return: 0
 */
int myunset_env(info *information)
{
	int i;

	if (information->argc == 1)
	{
		_errputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= information->argc; i++)
		unset_env(information, information->argv[i]);
	return (0);
}

/**
 * envlist_populating - populates env linked list
 * @information: structure containing potential args
 * Return: 0
 */
int envlist_populating(info *information)
{
	lists *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		node_end(&n, environ[i], 0);
	information->env = n;
	return (0);
}
