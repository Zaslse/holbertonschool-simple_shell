#include "shell.h"

/**
 * execute_cmd - Executes the command using fork and execve
 * @argv: Array of parsed arguments
 * @line: The original input string
 *
 * Return: The exit status of the executed command
 */
int execute_cmd(char **argv, char *line)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./hsh");
			free(line);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * print_env - Prints the current environment variables
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_command - Parses and executes one command
 * @input: Command to parse
 * @line: Original input line
 * @status: Current shell status
 *
 * Return: Command status
 */
int handle_command(char *input, char *line, int status)
{
	char *token, *argv[100], *p = input;
	int i;

	while (*p == ' ' || *p == '\t')
		p++;

	if (strncmp(p, "alias", 5) == 0 &&
	    (p[5] == '\0' || p[5] == '\n' ||
	     p[5] == ' ' || p[5] == '\t'))
		return (handle_alias(p));

	token = strtok(input, " \t\n");
	if (token == NULL)
		return (status);

	if (strcmp(token, "exit") == 0)
	{
		free_aliases();
		free(line);
		exit(status);
	}
	if (strcmp(token, "env") == 0)
	{
		print_env();
		return (status);
	}

	for (i = 0; token != NULL; i++)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	return (execute_cmd(argv, line));
}

/**
 * main - Simple shell entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL, *start, *p;
	size_t len = 0;
	int status = 0, run = 1;
	char operator = ';';

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		if (getline(&line, &len, stdin) == -1)
		{
			free_aliases();
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(status);
		}

		start = line;
		p = line;

		while (1)
		{
			if (*p == ';' ||
			    (*p == '&' && *(p + 1) == '&') ||
			    (*p == '|' && *(p + 1) == '|') ||
			    *p == '\0')
			{
				char next = *p;

				if (*p != '\0')
					*p = '\0';

				run = (operator == ';' ||
				       (operator == '&' && status == 0) ||
				       (operator == '|' && status != 0));

				if (run)
					status = handle_command(start, line, status);

				if (next == '\0')
					break;

				if (next == '&' || next == '|')
					p++;

				operator = next;
				start = p + 1;
			}
			p++;
		}
	}
	return (status);
}
