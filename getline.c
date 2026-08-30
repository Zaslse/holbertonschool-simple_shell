#include "shell.h"

/**
 * _getline - Custom getline implementation
 * @lineptr: Double pointer to buffer
 * @n: Pointer to buffer size
 * @fd: File descriptor
 * Return: Characters read, or -1
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFSIZE];
	static ssize_t b_pos;
	static ssize_t b_size;
	ssize_t len = 0;
	char *new_buf;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFSIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (b_pos >= b_size)
		{
			b_size = read(fd, buffer, BUFSIZE);
			b_pos = 0;
			if (b_size <= 0)
			{
				if (len == 0)
					return (-1);
				(*lineptr)[len] = '\0';
				return (len);
			}
		}
		while (b_pos < b_size)
		{
			if (len + 2 >= (ssize_t)*n)
			{
				*n += BUFSIZE;
				new_buf = malloc(*n);
				if (new_buf == NULL)
					return (-1);
				_strcpy(new_buf, *lineptr);
				free(*lineptr);
				*lineptr = new_buf;
			}
			(*lineptr)[len++] = buffer[b_pos];
			if (buffer[b_pos++] == '\n')
			{
				(*lineptr)[len] = '\0';
				return (len);
			}
		}
	}
}
