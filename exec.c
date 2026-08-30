#include "shell.h"

/**
 * find_path - Finds executable path
 * @info: Shell info
 * @cmd: Command
 * Return: Full path or NULL
 */
char *find_path(info_t *info, char *cmd)
{
	char *path = _getenv(info, "PATH");
	char *path_copy, *dir, *full_path;
	struct stat st;

	if (!path || _strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path_copy = _strdup(path);
	dir = _strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(_strlen(dir) + _strlen(cmd) + 2);
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute - Executes command
 * @info: Shell info
 * @args: Arguments
 * Return: 1
 */
int execute(info_t *info, char **args)
{
	char *cmd_path;
	pid_t pid;
	int status;

	cmd_path = find_path(info, args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			info->name, info->line_count, args[0]);
		info->status = 127;
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, info->env) == -1)
		{
			perror(info->name);
			exit(126);
		}
	}
	else if (pid < 0)
		perror(info->name);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			info->status = WEXITSTATUS(status);
	}

	free(cmd_path);
	return (1);
}
