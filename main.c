#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 * Return: Exit status
 */
int main(int ac, char **av)
{
	info_t info;
	size_t len = 0;
	ssize_t nread;
	int interactive;

	(void)ac;
	info.name = av[0];
	info.line = NULL;
	info.args = NULL;
	info.env = NULL;
	info.status = 0;
	info.count = 0;

	if (init_env(&info) == -1)
		return (1);

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);
		nread = _getline(&(info.line), &len, STDIN_FILENO);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		info.count++;
		handle_comments(info.line);
		info.args = tokenize(info.line);
		if (info.args != NULL && info.args[0] != NULL)
		{
			if (!check_builtin(&info))
				execute(&info);
		}
		if (info.args != NULL)
		{
			free_array(info.args);
			info.args = NULL;
		}
	}
	if (info.line != NULL)
		free(info.line);
	free_env(&info);
	return (info.status);
}
