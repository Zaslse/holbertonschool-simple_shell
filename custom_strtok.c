#include "shell.h"

/**
 * is_delim - Checks if a character is a delimiter
 * @c: Character to check
 * @delim: Delimiter string
 * Return: 1 if delimiter, 0 otherwise
 */
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - Custom strtok function
 * @str: String to tokenize
 * @delim: Delimiters
 * Return: Pointer to next token, or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *start;

	if (str != NULL)
		next = str;
	if (next == NULL || *next == '\0')
		return (NULL);

	while (*next && is_delim(*next, delim))
		next++;

	if (*next == '\0')
		return (NULL);

	start = next;
	while (*next && !is_delim(*next, delim))
		next++;

	if (*next)
	{
		*next = '\0';
		next++;
	}
	return (start);
}
