#include "shell.h"

/**
 * node_add - adding node
 *
 * @head: lists
 * @str: char
 * @num: int
 *
 * Return: lists
*/

lists *node_add(lists **head, const char *str, int num)
{
	lists *head_n;

	if (!head)
		return (NULL);
	head_n = malloc(sizeof(lists));
	if (!head_n)
		return (NULL);
	_memset((void *)head_n, 0, sizeof(lists));
	head_n->num = num;
	if (str)
	{
		head_n->str = _strdup(str);
		if (!head_n->str)
		{
			free(head_n);
			return (NULL);
		}
	}
	head_n->next = *head;
	*head = head_n;
	return (head_n);
}

/**
 * node_end - end of the node
 *
 * @head: pointer
 * @str: char
 * @num: int
 *
 * Return: lists
*/

lists *node_end(lists **head, const char *str, int num)
{
	lists *node_n, *n;

	if (!head)
		return (NULL);

	n = *head;
	node_n = malloc(sizeof(lists));
	if (!node_n)
		return (NULL);
	_memset((void *)node_n, 0, sizeof(lists));
	node_n->num = num;
	if (str)
	{
		node_n->str = _strdup(str);
		if (!node_n->str)
		{
			free(node_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = node_n;
	}
	else
		*head = node_n;
	return (node_n);
}

/**
 * print_list - print the list
 *
 * @h: const lists
 *
 * Return: size_t
*/

size_t print_list(const lists *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node - delete the node
 *
 * @head: pointer
 * @index: int
 *
 * Return: int
*/

int delete_node(lists **head, unsigned int index)
{
	lists *node_p, *n;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (x == index)
		{
			node_p->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		x++;
		node_p = n;
		n = n->next;
	}
	return (0);
}

/**
 * free_list - fre the list
 *
 * @head_p: lists
 *
 * Return: no
*/

void free_list(lists **head_p)
{
	lists *node_n, *n, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	n = head;
	while (n)
	{
		node_n = n->next;
		free(n->str);
		free(n);
		n = node_n;
	}
	*head_p = NULL;
}
