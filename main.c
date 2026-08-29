#include "shell.h"

/**
 * main - Simple shell entry point
 *
 * Description: A simple shell that reads input and handles the exit command.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(0);
		}

		if (line[0] == '\n')
			continue;

		token = strtok(line, " \n");
		if (token == NULL)
			continue;

		if (strcmp(token, "exit") == 0)
		{
			free(line);
			exit(0);
		}
	}

	return (0);
}
