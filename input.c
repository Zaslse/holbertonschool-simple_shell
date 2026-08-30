#include "shell.h"

/**
 * read_file_line - Reads one line from a file
 * @fd: File descriptor
 * @line: Line buffer
 * @size: Buffer size
 *
 * Return: 1 on success, 0 on EOF, or -1 on error
 */
int read_file_line(int fd, char **line, size_t *size)
{
	char c, *new;
	size_t pos = 0, new_size;
	ssize_t result;

	if (*line == NULL)
	{
		*size = 128;
		*line = malloc(*size);
		if (*line == NULL)
			return (-1);
	}

	while ((result = read(fd, &c, 1)) == 1)
	{
		if (pos + 1 >= *size)
		{
			new_size = *size * 2;
			new = malloc(new_size);
			if (new == NULL)
				return (-1);

			memcpy(new, *line, pos);
			free(*line);
			*line = new;
			*size = new_size;
		}

		(*line)[pos++] = c;

		if (c == '\n')
			break;
	}

	if (result == -1)
		return (-1);

	if (pos == 0)
		return (0);

	(*line)[pos] = '\0';
	return (1);
}
