#include "shell.h"

/**
 * hsh - main shell loop
 * @information: parameter and return info struct
 * @av: argument vector from main()
 * Return: 0 if success, 1 on error, or error code
 */
int hsh(info *information, char **av)
{
	ssize_t x = 0;
	int builtin_return = 0;

	while (x != -1 && builtin_return != -2)
	{
		clear_information(information);
		if (_interact(information))
			_puts("$ ");
		_errputchar(BUFFER_FLUSH);
		x = get_ip(information);
		if (x != -1)
		{
			set_information(information, av);
			builtin_return = builtin_find(information);
			if (builtin_return == -1)
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
	if (builtin_return == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_return);
}

/**
 * builtin_find - reaches builtin command
 * @information: return info struct
 * Return: -1 if not found, 0 if executed successfully,
 *		1 if found but not executed, -2 if builtin signals exit()
 */
int builtin_find(info *information)
{
	int i, builtin_return = -1;
	builtin_t builtintable[] = {
		{"exit", own_exit},
		{"env", current_env},
		{"help", own_help},
		{"history", my_history},
		{"setenv", myset_env},
		{"unsetenv", myunset_env},
		{"cd", own_cd},
		{"alias", own_alias},
		{NULL, NULL}};
	for (i = 0; builtintable[i].flag; i++)
		if (_strcmp(information->argv[0],
					builtintable[i].flag) == 0)
		{
			information->line_count++;
			builtin_return =
				builtintable[i].function(information);
			break;
		}
	return (builtin_return);
}

/**
 * command_find - finds command in PATH
 * @info: return info struct
 * Return: void
 */
void command_find(info *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = find_pathing(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		command_fork(info);
	}
	else
	{
		if ((_interact(info) || get_env(info, "PATH=") ||
					info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			command_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * command_fork - forks a an exec thread to run command
 * @information: return info struct
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
