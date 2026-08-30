#include "shell.h"

/**
 * split_line - Splits line into tokens
 * @line: Line to split
 * Return: Array of tokens
 */
char **split_line(char *line)
{
	int i = 0;
	char **tokens = malloc(1024 * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);
	token = _strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[i++] = token;
		token = _strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * main - Entry point
 * @ac: Arg count
 * @av: Arg vector
 * Return: Status
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	info_t info;
	int interactive = isatty(STDIN_FILENO), ret;

	(void)ac;
	info.name = av[0];
	info.line_count = 0;
	info.status = 0;
	init_env(&info);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);
		read = _getline(&line, &len, STDIN_FILENO);
		if (read == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		info.line_count++;
		args = split_line(line);
		if (args && args[0])
		{
			ret = check_builtin(&info, args);
			if (ret == -1)
			{
				free(args);
				break;
			}
			if (ret == 0)
				execute(&info, args);
		}
		free(args);
	}
	free(line);
	free_env(&info);
	return (info.status);
}
