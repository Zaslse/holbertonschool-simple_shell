#include "shell.h"

/**
 * _getline - Custom getline function
 * @lineptr: Pointer to line buffer
 * @n: Size of buffer
 * @fd: File descriptor to read from
 * Return: Number of characters read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buf[BUFSIZE];
	static ssize_t head = 0, tail = 0;
	ssize_t i, len = 0;
	char *new_ptr;

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
		if (head >= tail)
		{
			tail = read(fd, buf, BUFSIZE);
			head = 0;
			if (tail == 0)
				return (len == 0 ? -1 : len);
			if (tail < 0)
				return (-1);
		}
		while (head < tail)
		{
			if (len + 1 >= (ssize_t)*n)
			{
				*n += BUFSIZE;
				new_ptr = malloc(*n);
				if (!new_ptr)
					return (-1);
				for (i = 0; i < len; i++)
					new_ptr[i] = (*lineptr)[i];
				free(*lineptr);
				*lineptr = new_ptr;
			}
			(*lineptr)[len++] = buf[head];
			if (buf[head++] == '\n')
			{
				(*lineptr)[len] = '\0';
				return (len);
			}
		}
	}
}
