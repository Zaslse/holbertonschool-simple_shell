#include "shell.h"

/**
 * find_path - Resolves command full path from PATH variable
 * @info: Shell info struct
 * @cmd: Command name
 * Return: Allocated full path or NULL
 */
char *find_path(info_t *info, char *cmd)
{
	char *path_val, *path_copy, *token, *full;
	struct stat st;
	int len;

	if (cmd == NULL)
		return (NULL);
	if (_strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		return (NULL);
	}
	path_val = _getenv(info, "PATH");
	if (path_val == NULL || *path_val == '\0')
		return (NULL);
	path_copy = _strdup(path_val);
	if (path_copy == NULL)
		return (NULL);
	token = _strtok(path_copy, ":");
	while (token != NULL)
	{
		len = _strlen(token) + _strlen(cmd) + 2;
		full = malloc(sizeof(char) * len);
		if (full == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(full, token);
		_strcat(full, "/");
		_strcat(full, cmd);
		if (stat(full, &st) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		token = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
