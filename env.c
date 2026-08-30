#include "shell.h"

/**
 * init_env - Initializes environment array in info struct
 * @info: Shell info struct
 * Return: 0 on success, -1 on failure
 */
int init_env(info_t *info)
{
	int count = 0, i;

	while (environ[count])
		count++;
	info->env = malloc(sizeof(char *) * (count + 1));
	if (info->env == NULL)
		return (-1);
	for (i = 0; i < count; i++)
	{
		info->env[i] = _strdup(environ[i]);
		if (info->env[i] == NULL)
		{
			free_array(info->env);
			info->env = NULL;
			return (-1);
		}
	}
	info->env[count] = NULL;
	return (0);
}

/**
 * free_env - Frees shell environment array
 * @info: Shell info struct
 */
void free_env(info_t *info)
{
	if (info->env != NULL)
	{
		free_array(info->env);
		info->env = NULL;
	}
}

/**
 * _getenv - Gets value of an environment variable
 * @info: Shell info struct
 * @name: Variable name
 * Return: Pointer to value or NULL
 */
char *_getenv(info_t *info, const char *name)
{
	int i, len;

	if (info == NULL || info->env == NULL || name == NULL)
		return (NULL);
	len = _strlen(name);
	for (i = 0; info->env[i] != NULL; i++)
	{
		if (_strncmp(info->env[i], name, len) == 0 && info->env[i][len] == '=')
			return (info->env[i] + len + 1);
	}
	return (NULL);
}

/**
 * _setenv - Sets or updates an environment variable
 * @info: Shell info struct
 * @name: Variable name
 * @value: Variable value
 * Return: 0 on success, -1 on failure
 */
int _setenv(info_t *info, const char *name, const char *value)
{
	int i, count = 0, len;
	char *new_entry, **new_env;

	if (info == NULL || name == NULL || value == NULL)
		return (-1);
	len = _strlen(name) + _strlen(value) + 2;
	new_entry = malloc(sizeof(char) * len);
	if (new_entry == NULL)
		return (-1);
	_strcpy(new_entry, name);
	_strcat(new_entry, "=");
	_strcat(new_entry, value);
	len = _strlen(name);
	for (i = 0; info->env[i] != NULL; i++)
	{
		if (_strncmp(info->env[i], name, len) == 0 && info->env[i][len] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_entry;
			return (0);
		}
	}
	while (info->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (new_env == NULL)
	{
		free(new_entry);
		return (-1);
	}
	for (i = 0; i < count; i++)
		new_env[i] = info->env[i];
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	free(info->env);
	info->env = new_env;
	return (0);
}

/**
 * _unsetenv - Unsets an environment variable
 * @info: Shell info struct
 * @name: Variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(info_t *info, const char *name)
{
	int i, j, len;

	if (info == NULL || info->env == NULL || name == NULL)
		return (-1);
	len = _strlen(name);
	for (i = 0; info->env[i] != NULL; i++)
	{
		if (_strncmp(info->env[i], name, len) == 0 && info->env[i][len] == '=')
		{
			free(info->env[i]);
			for (j = i; info->env[j] != NULL; j++)
				info->env[j] = info->env[j + 1];
			return (0);
		}
	}
	return (0);
}
