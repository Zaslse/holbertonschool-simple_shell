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
	char *args[2];
	size_t len = 0;
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
		line[strcspn(line, "\n")] = '\0';
		if (line[0] == '\0')
			continue;
		pid = fork();
		if (pid == 0)
		{
			args[0] = line;
			args[1] = NULL;
			execve(line, args, environ);
			perror(argv[0]);
			_exit(1);
		}
		wait(NULL);
	}
}
