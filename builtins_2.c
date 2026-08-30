#include "shell.h"

/**
 * _setenv - Sets environment variable
 * @info: Shell info
 * @name: Name of var
 * @value: Value of var
 * Return: 1 on success
 */
int _setenv(info_t *info, char *name, char *value)
{
	int i, len;
	char *new_var, *tmp;

	if (!name || !value)
		return (0);

	len = _strlen(name) + _strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (0);
	_strcpy(new_var, name);
	_strcat(new_var, "=");
	_strcat(new_var, value);

	len = _strlen(name);
	for (i = 0; info->env[i]; i++)
	{
		if (_strncmp(info->env[i], name, len) == 0 && info->env[i][len] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_var;
			return (1);
		}
	}

	tmp = (char *)info->env;
	info->env = malloc(sizeof(char *) * (i + 2));
	if (!info->env)
	{
		free(new_var);
		return (0);
	}
	for (i = 0; ((char **)tmp)[i]; i++)
		info->env[i] = ((char **)tmp)[i];
	info->env[i] = new_var;
	info->env[i + 1] = NULL;
	free(tmp);
	return (1);
}

/**
 * shell_setenv - Builtin setenv
 * @info: Shell info
 * @args: Arguments
 * Return: 1
 */
int shell_setenv(info_t *info, char **args)
{
	if (!args[1] || !args[2])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	_setenv(info, args[1], args[2]);
	return (1);
}

/**
 * _unsetenv - Unsets environment variable
 * @info: Shell info
 * @name: Name of var
 * Return: 1 on success
 */
int _unsetenv(info_t *info, char *name)
{
	int i, j, len;

	if (!name)
		return (0);
	len = _strlen(name);
	for (i = 0; info->env[i]; i++)
	{
		if (_strncmp(info->env[i], name, len) == 0 && info->env[i][len] == '=')
		{
			free(info->env[i]);
			for (j = i; info->env[j]; j++)
				info->env[j] = info->env[j + 1];
			return (1);
		}
	}
	return (0);
}

/**
 * shell_unsetenv - Builtin unsetenv
 * @info: Shell info
 * @args: Arguments
 * Return: 1
 */
int shell_unsetenv(info_t *info, char **args)
{
	if (!args[1])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}
	_unsetenv(info, args[1]);
	return (1);
}
