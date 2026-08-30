#include "shell.h"

/**
 * check_builtin - Checks and executes builtins
 * @info: Shell info struct
 * @args: Arguments
 * Return: 1 if builtin executed, 0 otherwise
 */
int check_builtin(info_t *info, char **args)
{
	if (_strcmp(args[0], "exit") == 0)
		return (shell_exit(info, args));
	if (_strcmp(args[0], "cd") == 0)
		return (shell_cd(info, args));
	if (_strcmp(args[0], "env") == 0)
		return (shell_env(info, args));
	if (_strcmp(args[0], "setenv") == 0)
		return (shell_setenv(info, args));
	if (_strcmp(args[0], "unsetenv") == 0)
		return (shell_unsetenv(info, args));
	return (0);
}

/**
 * shell_exit - Exits the shell
 * @info: Shell info struct
 * @args: Arguments
 * Return: 1 on failure, -1 to signal exit
 */
int shell_exit(info_t *info, char **args)
{
	int status = info->status;

	if (args[1])
	{
		status = _atoi(args[1]);
		if (status < 0 || (status == 0 && args[1][0] != '0'))
		{
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				info->name, info->line_count, args[1]);
			info->status = 2;
			return (1);
		}
		info->status = status;
	}
	return (-1);
}

/**
 * shell_env - Prints the environment
 * @info: Shell info struct
 * @args: Arguments
 * Return: 1
 */
int shell_env(info_t *info, char **args)
{
	int i;

	(void)args;
	for (i = 0; info->env[i]; i++)
	{
		write(STDOUT_FILENO, info->env[i], _strlen(info->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * shell_cd - Changes directory
 * @info: Shell info struct
 * @args: Arguments
 * Return: 1
 */
int shell_cd(info_t *info, char **args)
{
	char *dir = args[1];
	char cwd[1024];

	if (!dir)
		dir = _getenv(info, "HOME");
	else if (_strcmp(dir, "-") == 0)
	{
		dir = _getenv(info, "OLDPWD");
		if (!dir)
			dir = getcwd(cwd, 1024);
		printf("%s\n", dir);
	}

	if (chdir(dir) == -1)
	{
		fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
			info->name, info->line_count, args[1]);
		return (1);
	}

	_setenv(info, "OLDPWD", _getenv(info, "PWD"));
	if (getcwd(cwd, 1024))
		_setenv(info, "PWD", cwd);
	return (1);
}
