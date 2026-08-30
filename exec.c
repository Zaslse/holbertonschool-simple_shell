#include "shell.h"

/**
 * handle_comments - Truncates command line at first # preceded by space
 * @line: Command line
 */
void handle_comments(char *line)
{
	int i;

	if (line == NULL)
		return;
	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#' && (i == 0 || line[i - 1] == ' ' || line[i - 1] == '\t'))
		{
			line[i] = '\0';
			break;
		}
	}
}

/**
 * execute - Forks and executes external program
 * @info: Shell info struct
 * Return: Exit status
 */
int execute(info_t *info)
{
	char *cmd_path;
	pid_t child_pid;
	int status;

	cmd_path = find_path(info, info->args[0]);
	if (cmd_path == NULL)
	{
		print_error(info, "not found");
		info->status = 127;
		return (info->status);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror(info->name);
		free(cmd_path);
		info->status = 1;
		return (info->status);
	}
	if (child_pid == 0)
	{
		if (execve(cmd_path, info->args, info->env) == -1)
		{
			perror(info->name);
			free(cmd_path);
			exit(126);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			info->status = WEXITSTATUS(status);
	}
	free(cmd_path);
	return (info->status);
}
