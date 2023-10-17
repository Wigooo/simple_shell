#include "shell.h"

/**
 * _memset - fills memo with constant byte
 * @memo_ptr: pointer to memo area
 * @bytes: byte to fill *memo_ptr with
 * @n: number of bytes be filled
 * Return: memo_ptr pointer to memo area
 */

char *_memset(char *memo_ptr, char bytes, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		memo_ptr[i] = bytes;
	}
	return (memo_ptr);
}

/**
 * _free - frees a string of strings
 * @ss: string of strings
 */
void _free(char **ss)
{
	char **p = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(p);
}

/**
 * _realloc - reallocates block of memo
 * @pointer: pointer to pre mallocated block
 * @old_size: bytes of pre block
 * @new_size: bytes of new block
 * Return: pointer to allocated memo
 */

void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *ptr;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);

	ptr = malloc(new_size);

	if (!ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		ptr[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (ptr);
}

/**
 * pfree - frees a pointer and NULLS the address
 * @pointer: address of pointer being freed
 * Return: 1 if freed, 0 otherwise
 */

int pfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
