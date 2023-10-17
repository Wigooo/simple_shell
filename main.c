#include "shell.h"

/**
 * main - entry point
 *
 * @ac: int
 * @av: pointer
 *
 * Return: int
 */

int main(int ac, char **av)
{
	info inf[] = { INFO_INIT };
	int x = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(x)
		: "r"(x));

	if (ac == 2)
	{
		x = open(av[1], O_RDONLY);
		if (x == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(av[0]);
				_errputs(": 0: Can't open ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = x;
	}
	envlist_populating(inf);
	history_read(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
