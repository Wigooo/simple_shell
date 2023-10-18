#include "shell.h"

/**
 * hsh - main shell loop
 * @information: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info *information, char **av)
{
	ssize_t x = 0;
	int builtin = 0;

	while (x != -1 && builtin != -2)
	{
		clear_information(information);
		if (_interact(information))
			_puts("$ ");
		_errputchar(BUFFER_FLUSH);
		x = get_ip(information);
		if (x != -1)
		{
			set_information(information, av);
			builtin = builtin_find(information);
			if (builtin == -1)
				command_find(information);
		}
		else if (_interact(information))
			_putchar('\n');
		free_information(information, 0);
	}
	history_write(information);
	free_information(information, 1);
	if (!_interact(information) && information->status)
		exit(information->status);
	if (builtin == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin);
}

/**
 * builtin_find - finds a builtin command
 * @information: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtin_find(info *information)
{
	int i, builtin_ret = -1;
	builtin_t builtintable[] = {
		{"exit", own_exit},
		{"env", current_env},
		{"help", own_help},
		{"history", my_history},
		{"setenv", myset_env},
		{"unsetenv", myunset_env},
		{"cd", own_cd},
		{"alias", own_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].flag; i++)
		if (_strcmp(information->argv[0], builtintable[i].flag) == 0)
		{
			information->line_count++;
			builtin_ret = builtintable[i].function(information);
			break;
		}
	return (builtin_ret);
}

/**
 * command_find - finds a command in PATH
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void command_find(info *information)
{
	char *path = NULL;
	int i, j;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (i = 0, j = 0; information->arg[i]; i++)
		if (!is_delimeter(information->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_pathing(information, get_env(information, "PATH="),
	information->argv[0]);
	if (path)
	{
		information->path = path;
		command_fork(information);
	}
	else
	{
		if ((_interact(information) || get_env(information, "PATH=")
			|| information->argv[0][0] == '/') &&
			is_cmd(information, information->argv[0]))
			command_fork(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_err(information, "not found\n");
		}
	}
}

/**
 * command_fork - forks a an exec thread to run cmd
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void command_fork(info *information)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(information->path, information->argv,
		print_environ(information)) == -1)
		{
			free_information(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_err(information, "Permission denied\n");
		}
	}
}
