#include "shell.h"

/**
 * unset_env - removes env variable
 * @information: structure containing potential args
 * @var: string env var
 * Return: 1 if success, 0 otherwise
 */
int unset_env(info *information, char *var)
{
	lists *n = information->env;
	size_t i = 0;
	char *ptr;

	if (!n || !var)
		return (0);

	while (n)
	{
		ptr = _starting_with(n->str, var);
		if (ptr && *ptr == '=')
		{
			information->env_changed = delete_node(&(information->env), i);
			i = 0;
			n = information->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (information->env_changed);
}

/**
 * set_env - change or add new enviroment variable
 * @information: structure containing potential args
 * @var: env var property
 * @value: string env var value
 * Return: 0
 */
int set_env(info *information, char *var, char *value)
{
	char *buffer = NULL;
	lists *n;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, '=');
	_strcat(buffer, value);
	n = information->env;

	while (n)
	{
		ptr = _starting_with(n->str, var);
		if (ptr && *ptr == '=')
		{
			free(n->str);
			n->str = buffer;
			information->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	node_end(&(information->env), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}

/**
 * print_environ - return str array copy of environ
 * @information: structure containing potential args
 * Return: 0
 */
char **print_environ(info *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = ls_to_str(information->env);
		information->env_changed = 0;
	}
	return (information->environ);
}
