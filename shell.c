#include "shell.h"

/**
 * execute_cmd - Executes the command using fork and execve
 * @argv: Array of parsed arguments
 * @line: The original input string
 * @command: Parsed command string
 *
 * Return: The exit status of the executed command
 */
int execute_cmd(char **argv, char *line, char *command)
{
	pid_t child_pid;
	int status = 0;
	char *path;

	path = find_command_path(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "./hsh: No such file or directory\n");
		return (127);
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("./hsh");
			free(path);
			free(command);
			free_aliases();
			free(line);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(path);

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
 * expand_alias - Expands aliases in a command
 * @input: Command input
 *
 * Return: Expanded command
 */
char *expand_alias(char *input)
{
	char *command, *p, *value, *new, saved;
	int count = 0;

	command = strdup(input);
	if (command == NULL)
		return (NULL);

	while (count++ < 100)
	{
		p = command;

		while (*p == ' ' || *p == '\t')
			p++;

		while (*p != ' ' && *p != '\t' &&
		       *p != '\n' && *p != '\0')
			p++;

		saved = *p;
		*p = '\0';
		value = find_alias(command, NULL);
		*p = saved;

		if (value == NULL)
			break;

		new = malloc(strlen(value) + strlen(p) + 1);
		if (new == NULL)
			break;

		sprintf(new, "%s%s", value, p);
		free(command);
		command = new;
	}

	return (command);
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
	char *token, *argv[100], *p = input, *command;
	int i, result;

	while (*p == ' ' || *p == '\t')
		p++;

	if (strncmp(p, "alias", 5) == 0 &&
	    (p[5] == '\0' || p[5] == '\n' ||
	     p[5] == ' ' || p[5] == '\t'))
		return (handle_alias(p));

	command = expand_alias(input);
	if (command == NULL)
		return (status);

	p = expand_variables(command, status);
	free(command);
	command = p;

	if (command == NULL)
		return (status);

	token = strtok(command, " \t\n");
	if (token == NULL)
	{
		free(command);
		return (status);
	}

	if (strcmp(token, "exit") == 0)
	{
		free(command);
		free_aliases();
		free(line);
		exit(status);
	}

	if (strcmp(token, "env") == 0)
	{
		print_env();
		free(command);
		return (status);
	}

	if (strcmp(token, "help") == 0)
	{
		token = strtok(NULL, " \t\n");
		print_help(token);
		free(command);
		return (0);
	}

	for (i = 0; token != NULL; i++)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	result = execute_cmd(argv, line, command);
	free(command);

	return (result);
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

		remove_comment(line);

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
