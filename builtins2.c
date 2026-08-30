#include "shell.h"

/**
 * builtin_cd - Handles cd builtin command
 * @info: Shell info struct
 * Return: 1 on success
 */
int builtin_cd(info_t *info)
{
	char *target, cwd[1024];
	char *pwd = _getenv(info, "PWD");
	char *oldpwd = _getenv(info, "OLDPWD");
	int print_path = 0;

	if (!info->args[1] || _strcmp(info->args[1], "~") == 0)
	{
		target = _getenv(info, "HOME");
		if (!target)
			target = pwd;
	}
	else if (_strcmp(info->args[1], "-") == 0)
	{
		target = oldpwd ? oldpwd : pwd;
		print_path = 1;
	}
	else
	{
		target = info->args[1];
	}

	if (!target)
		target = "/";

	if (chdir(target) == -1)
	{
		print_custom_error(info, "cd", "can't cd to ");
		write(STDERR_FILENO, info->args[1], _strlen(info->args[1]));
		write(STDERR_FILENO, "\n", 1);
		info->status = 2;
		return (1);
	}

	if (print_path)
	{
		write(STDOUT_FILENO, target, _strlen(target));
		write(STDOUT_FILENO, "\n", 1);
	}

	_setenv(info, "OLDPWD", pwd ? pwd : "");
	if (getcwd(cwd, sizeof(cwd)))
		_setenv(info, "PWD", cwd);

	info->status = 0;
	return (1);
}
