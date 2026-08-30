#include "shell.h"

static char *history_list[4096];
static int history_count;
static int history_first;

/**
 * history_add - Adds a command to history
 * @line: Command line
 */
void history_add(char *line)
{
	char *copy;
	int length;

	length = strlen(line);
	while (length > 0 && line[length - 1] == '\n')
		length--;

	copy = malloc(length + 1);
	if (copy == NULL)
		return;

	strncpy(copy, line, length);
	copy[length] = '\0';

	if (history_count == 4096)
	{
		free(history_list[0]);
		memmove(history_list, history_list + 1,
			sizeof(char *) * 4095);
		history_count--;
		history_first = (history_first + 1) % 4096;
	}

	history_list[history_count++] = copy;
}

/**
 * history_print - Prints command history
 */
void history_print(void)
{
	int i;

	for (i = 0; i < history_count; i++)
		printf("%d %s\n", (history_first + i) % 4096,
			   history_list[i]);
}

/**
 * history_init - Loads history from file
 */
void history_init(void)
{
	char *home = NULL, *path, line[4096];
	int fd, i, pos = 0, total = 0;
	char c;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "HOME=", 5) == 0)
		{
			home = environ[i] + 5;
			break;
		}
	}

	if (home == NULL)
		return;

	path = malloc(strlen(home) + 23);
	if (path == NULL)
		return;

	sprintf(path, "%s/.simple_shell_history", home);
	fd = open(path, O_RDONLY);
	free(path);

	if (fd == -1)
		return;

	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
		{
			line[pos] = '\0';
			history_add(line);
			total++;
			pos = 0;
		}
		else if (pos < 4095)
			line[pos++] = c;
	}

	if (pos > 0)
	{
		line[pos] = '\0';
		history_add(line);
		total++;
	}

	close(fd);

	if (total >= history_count)
		history_first = (total - history_count) % 4096;
}

/**
 * history_save - Saves history to file
 */
void history_save(void)
{
	char *home = NULL, *path;
	int fd, i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "HOME=", 5) == 0)
		{
			home = environ[i] + 5;
			break;
		}
	}

	if (home == NULL)
		return;

	path = malloc(strlen(home) + 23);
	if (path == NULL)
		return;

	sprintf(path, "%s/.simple_shell_history", home);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	free(path);

	if (fd == -1)
		return;

	for (i = 0; i < history_count; i++)
	{
		write(fd, history_list[i], strlen(history_list[i]));
		write(fd, "\n", 1);
	}

	close(fd);
}

/**
 * history_free - Frees history memory
 */
void history_free(void)
{
	int i;

	for (i = 0; i < history_count; i++)
		free(history_list[i]);
}
