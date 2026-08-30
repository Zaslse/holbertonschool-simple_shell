#include "shell.h"

/**
 * init_env - Initializes environment
 * @info: Shell info
 * Return: 1 on success
 */
int init_env(info_t *info)
{
	int i = 0;

	while (environ[i])
		i++;
	info->env = malloc(sizeof(char *) * (i + 1));
	if (!info->env)
		return (0);
	for (i = 0; environ[i]; i++)
		info->env[i] = _strdup(environ[i]);
	info->env[i] = NULL;
	return (1);
}

/**
 * free_env - Frees environment
 * @info: Shell info
 */
void free_env(info_t *info)
{
	int i;

	if (info->env)
	{
		for (i = 0; info->env[i]; i++)
			free(info->env[i]);
		free(info->env);
	}
}

/**
 * _getenv - Gets environment variable
 * @info: Shell info
 * @name: Name of var
 * Return: Value of var, or NULL
 */
char *_getenv(info_t *info, const char *name)
{
	int i, len;

	len = _strlen((char *)name);
	for (i = 0; info->env[i]; i++)
	{
		if (_strncmp(info->env[i], (char *)name, len) == 0 &&
			info->env[i][len] == '=')
			return (info->env[i] + len + 1);
	}
	return (NULL);
}
