#include "shell.h"

/**
 * get_path - Gets the PATH environment variable
 *
 * Return: PATH value or NULL
 */
static char *get_path(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_command_path - Finds a command in PATH
 * @command: Command name
 *
 * Return: Full command path or NULL
 */
char *find_command_path(char *command)
{
	char *path, *copy, *dir, *full;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = get_path();
	if (path == NULL)
		return (NULL);

	copy = strdup(path);
	if (copy == NULL)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir != NULL)
	{
		full = malloc(strlen(dir) + strlen(command) + 2);
		if (full == NULL)
		{
			free(copy);
			return (NULL);
		}

		sprintf(full, "%s/%s", dir, command);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}

		free(full);
		dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}
