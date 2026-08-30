#include "shell.h"

/**
 * print_error - Prints standard shell error message
 * @info: Shell info struct
 * @msg: Error message to display
 */
void print_error(info_t *info, const char *msg)
{
	char *cnt = _itoa(info->count);

	write(STDERR_FILENO, info->name, _strlen(info->name));
	write(STDERR_FILENO, ": ", 2);
	if (cnt != NULL)
	{
		write(STDERR_FILENO, cnt, _strlen(cnt));
		free(cnt);
	}
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, info->args[0], _strlen(info->args[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * print_custom_error - Prints custom formatted error message
 * @info: Shell info struct
 * @cmd: Builtin or command name
 * @msg: Specific error message
 */
void print_custom_error(info_t *info, const char *cmd, const char *msg)
{
	char *cnt = _itoa(info->count);

	write(STDERR_FILENO, info->name, _strlen(info->name));
	write(STDERR_FILENO, ": ", 2);
	if (cnt != NULL)
	{
		write(STDERR_FILENO, cnt, _strlen(cnt));
		free(cnt);
	}
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, _strlen(msg));
}
