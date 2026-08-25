#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Simple UNIX command interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char **args;
	char *token;
	size_t len = 0;
	int index;
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

		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, environ);
			perror(argv[0]);
			free(args);
			free(line);
			_exit(1);
		}
		wait(NULL);
		free(args);
	}
}
