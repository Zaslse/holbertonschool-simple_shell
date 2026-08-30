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

	if (info->args[1] == NULL || _strcmp(info->args[1], "~") == 0)
	{
		target = _getenv(info, "HOME");
		if (target == NULL)
			target = pwd;
	}
	else if (_strcmp(info->args[1], "-") == 0)
	{
		if (oldpwd == NULL)
		{
			target = pwd;
			if (pwd != NULL)
			{
				write(STDOUT_FILENO, pwd, _strlen(pwd));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		else
		{
			target = oldpwd;
			write(STDOUT_FILENO, oldpwd, _strlen(oldpwd));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		target = info->args[1];

	if (target == NULL)
		target = "/";

	if (chdir(target) == -1)
	{
		print_custom_error(info, "cd", "can't cd to ");
		write(STDERR_FILENO, info->args[1], _strlen(info->args[1]));
		write(STDERR_FILENO, "\n", 1);
		info->status = 2;
		return (1);
	}

	_setenv(info, "OLDPWD", pwd ? pwd : "");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		_setenv(info, "PWD", cwd);
	
	info->status = 0;
	return (1);
}
