#include "shell.h"

/**
 * check_builtin - Checks if command is a builtin and executes it
 * @info: Shell info struct
 * Return: 1 if builtin found, 0 otherwise
 */
int check_builtin(info_t *info)
{
	if (_strcmp(info->args[0], "exit") == 0)
		return (builtin_exit(info));
	if (_strcmp(info->args[0], "env") == 0)
		return (builtin_env(info));
	if (_strcmp(info->args[0], "setenv") == 0)
		return (builtin_setenv(info));
	if (_strcmp(info->args[0], "unsetenv") == 0)
		return (builtin_unsetenv(info));
	if (_strcmp(info->args[0], "cd") == 0)
		return (builtin_cd(info));
	return (0);
}

/**
 * builtin_exit - Handles exit builtin
 * @info: Shell info struct
 * Return: 1 to exit or 2 on error
 */
int builtin_exit(info_t *info)
{
	int exit_val;

	if (info->args[1] != NULL)
	{
		exit_val = _atoi(info->args[1]);
		if (exit_val < 0)
		{
			print_custom_error(info, "exit", "Illegal number: ");
			write(STDERR_FILENO, info->args[1], _strlen(info->args[1]));
			write(STDERR_FILENO, "\n", 1);
			info->status = 2;
			return (2);
		}
		info->status = exit_val;
	}
	free_array(info->args);
	info->args = NULL;
	if (info->line)
	{
		free(info->line);
		info->line = NULL;
	}
	free_env(info);
	exit(info->status);
}

/**
 * builtin_env - Handles env builtin
 * @info: Shell info struct
 * Return: 1 on success
 */
int builtin_env(info_t *info)
{
	int i;

	if (info->env == NULL)
		return (1);
	for (i = 0; info->env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, info->env[i], _strlen(info->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	info->status = 0;
	return (1);
}

/**
 * builtin_setenv - Handles setenv builtin
 * @info: Shell info struct
 * Return: 1 on success
 */
int builtin_setenv(info_t *info)
{
	if (info->args[1] == NULL || info->args[2] == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
		info->status = 1;
		return (1);
	}
	if (_setenv(info, info->args[1], info->args[2]) == -1)
	{
		perror(info->name);
		info->status = 1;
		return (1);
	}
	info->status = 0;
	return (1);
}

/**
 * builtin_unsetenv - Handles unsetenv builtin
 * @info: Shell info struct
 * Return: 1 on success
 */
int builtin_unsetenv(info_t *info)
{
	if (info->args[1] == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 25);
		info->status = 1;
		return (1);
	}
	if (_unsetenv(info, info->args[1]) == -1)
	{
		perror(info->name);
		info->status = 1;
		return (1);
	}
	info->status = 0;
	return (1);
}
