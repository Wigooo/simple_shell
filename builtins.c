#include "shell.h"

/**
 * own_exit - exits shell
 * @information: structure containing potential args
 * Return: exits with given exit status, 0 if info.argv[0] != "exit"
 */
int own_exit(info *information)
{
	int is_exit;

	if (information->argv[1])
	{
		is_exit = _erroratoi(information->argv[1]);
		if (is_exit == -1)
		{
			information->status = 2;
			print_err(information, "Illegal number: ");
			_errputs(information->argv[1]);
			_errputchar('\n');
			return (1);
		}
		information->err_num = _erroratoi(information->argv[1]);
		return (-2);
	}
	information->err_num = -1;
	return (-2);
}

/**
 * own_cd - change directory
 * @information: structure containing potential args
 * Return: 0
 */
int own_cd(info *information)
{
	char buffer[1024], *directory, *s;
	int change_directory_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!information->argv[1])
	{
		directory = get_env(information, "HOME=");
		if (!directory)
			change_directory_ret =
				chdir((directory = get_env(information, "PWD=")) ? directory : "/");
		else
			change_directory_ret = chdir(directory);
	}
	else if (_strcmp(information->argv[1], "-") == 0)
	{
		if (!get_env(information, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(information, "OLDPWD=")), _putchar('\n');
		change_directory_ret =
			chdir((directory = get_env(information, "OLDPWD=")) ? directory : "/");
	}
	else
		change_directory_ret = chdir(information->argv[1]);
	if (change_directory_ret == -1)
	{
		print_err(information, "can't cd to ");
		_errputs(information->argv[1]), _errputchar('\n');
	}
	else
	{
		set_env(information, "OLDPWD", get_env(information, "PWD="));
		set_env(information, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * own_help - changes current dir of process
 * @information: structure containing potential of args
 * Return: 0
 */
int own_help(info *information)
{
	char **args_arr;

	args_arr = information->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*args_arr);
	return (0);
}
