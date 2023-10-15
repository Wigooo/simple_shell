#include "shell.h"

/**
 * chain_check - checks if should chain based on last status
 * @information: struct parameter
 * @buffer: character buffer
 * @ap: address of current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 * Return: void
 */
void chain_check(info *information,
		char *buffer, size_t *ap, size_t start, size_t length)
{
	size_t x = *ap;

	if (information->cmd_buf_type == AND)
	{
		if (information->status)
		{
			buffer[start] = 0;
			x = length;
		}
	}
	if (information->cmd_buf_type == OR)
	{
		if (!information->status)
		{
			buffer[start] = 0;
			x = length;
		}
	}
	*ap = x;
}

/**
 * is_chain - checks if character a chain del.
 * @information: struct parameter
 * @buffer: char buff
 * @ap: address of current position in buffer
 * Return: 1 if chain, 0 otherwise
 */
int is_chain(info *information, char *buffer, size_t *ap)
{
	size_t x = *ap;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		information->cmd_buf_type = OR;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		information->cmd_buf_type = AND;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		information->cmd_buf_type = CHAIN;
	}
	else
		return (0);
	*ap = x;
	return (1);
}

/**
 * alias_replace - replaces an aliases in tokensized str
 * @information: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info *information)
{
	int i;
	lists *node;
	char *ap;

	for (i = 0; i < 10; i++)
	{
		node = starting_with_node(information->alias, information->argv[0], '=');
		if (!node)
			return (0);
		free(information->argv[0]);
		ap = _strchr(node->str, '=');
		if (!ap)
			return (0);
		information->argv[0] = ap;
	}
	return (1);
}

/**
 * string_replace - replaces string
 * @old_str: address of old string
 * @new_str: new string
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **old_str, char **new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

/**
 * vars_replace - replaces vars
 * @information: struct parameter
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info *information)
{
	int i = 0;
	lists *node;

	for (i = 0; information->argv[i]; i++)
	{
		if (information->argv[i][0] != '$' || !information->argv[i][1])
			continue;
		if (!_strcmp(information->argv[i], "$?"))
		{
			string_replace(&(information->argv[i]),
					_strdup(number_convert(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[i], "$$"))
		{
			string_replace(&(information->argv[i]),
					_strdup(number_convert(get_pid(), 10, 0)));
			continue;
		}
		node = starting_with_node(information->env, &information->argv[i][1], '=');
		if (node)
		{
			string_replace(&(information->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_replace(&information->argv[i], _strdup(""));
	}
	return (0);
}
