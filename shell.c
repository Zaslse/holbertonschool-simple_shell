#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * find_command - Finds a command in PATH
 * @command: Command to find
 *
 * Return: Full path or NULL
 */
char *find_command(char *command)
{
	char *path = NULL, *copy, *dir, *full;
	int i;

	if (strchr(command, '/') != NULL)
		return (access(command, X_OK) == 0 ? strdup(command) : NULL);

	for (i = 0; environ[i] != NULL; i++)
		if (strncmp(environ[i], "PATH=", 5) == 0)
			path = environ[i] + 5;

	if (path == NULL)
		return (NULL);

	copy = strdup(path);
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

/**
 * main - Simple UNIX command interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL, **args, *token, *command;
	size_t len = 0;
	int index, count = 0;
	pid_t pid;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");
		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			return (0);
		}

		args = malloc(sizeof(char *) * len);
		if (args == NULL)
		{
			free(line);
			return (1);
		}

		index = 0;
		token = strtok(line, " \n");
		while (token != NULL)
		{
			args[index++] = token;
			token = strtok(NULL, " \n");
		}
		args[index] = NULL;

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		count++;
		command = find_command(args[0]);
		if (command == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], count, args[0]);
			free(args);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(command, args, environ);
			_exit(1);
		}
		wait(NULL);
		free(command);
		free(args);
	}
}
