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
	static char buf[BUFSIZE];
	static ssize_t head = 0, tail = 0;
	ssize_t len = 0, i;
	char *new_ptr;

	if (!lineptr || !n)
		return (-1);
	if (!*lineptr || *n == 0)
	{
		*n = BUFSIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}
	while (1)
	{
		if (head >= tail)
		{
			tail = read(fd, buf, BUFSIZE);
			head = 0;
			if (tail == 0)
			{
				if (len == 0)
					return (-1);
				(*lineptr)[len] = '\0';
				return (len);
			}
			if (tail < 0)
				return (-1);
		}
		while (head < tail)
		{
			if (len >= (ssize_t)(*n) - 1)
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
			(*lineptr)[len++] = buf[head++];
			if (buf[head - 1] == '\n')
			{
				(*lineptr)[len] = '\0';
				return (len);
			}
		}
	}
}
