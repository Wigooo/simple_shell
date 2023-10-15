#include "shell.h"

/**
 * list_length - calc length of linked list
 * @head: pointer to first node
 * Return: list size
 */
size_t list_length(const lists *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * ls_to_str - returns an array of strings of list->str
 * @h: pointer to head node
 * Return: arr of strings
 */
char **ls_to_str(lists *h)
{
	lists *node = h;
	size_t i = list_length(h), j;
	char **strings;
	char *string;

	if (!h || !i)
	{
		return (NULL);
	}
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			return (NULL);
		}
		string = _strcpy(string, node->str);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * print_ls - prints elements of lists linked list
 * @head: pointer to head node
 * Return: list size
 */
size_t print_ls(const lists *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(number_convert(head->num, 10, 0));
		_putchar(":");
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * starting_with_node - returns node whose string starts with prefix
 * @head_node: pointer to head
 * @pre: string to match
 * @c: next character after prefix to match
 * Return: match node or NULL
 */
lists *starting_with_node(lists *head_node, char *pre, char c)
{
	char *p = NULL;

	while (head_node)
	{
		p = _starting_with(head_node->str, pre);
		if (p && ((c == -1) || (*p == c)))
			return (head_node);
		head_node = head_node->next;
	}
	return (NULL);
}

/**
 * getting_node_idx - gets index of node
 * @h: points to list head
 * @node: points to required node
 * Return: idx of node , -1 if fail
 */
ssize_t getting_node_idx(lists *h, lists *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
