#include "shell.h"

/**
 * execute_cmd - Executes the command using fork and execve
 * @argv: Array of parsed arguments
 * @line: The original input string
 */
void execute_cmd(char **argv, char *line)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./hsh");
			free(line);
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Simple shell entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL, *token, *argv[100];
	size_t len = 0;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(0);
		}
		token = strtok(line, " \n");
		if (token == NULL)
			continue;
		if (strcmp(token, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		for (i = 0; token != NULL; i++)
		{
			argv[i] = token;
			token = strtok(NULL, " \n");
		}
		argv[i] = NULL;
		execute_cmd(argv, line);
	}
	return (0);
}
