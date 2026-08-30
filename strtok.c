#include "shell.h"

/**
 * is_delim - Checks if character is delimiter
 * @c: Character
 * @delim: Delimiter string
 * Return: 1 if delimiter, 0 otherwise
 */
static int is_delim(char c, const char *delim)
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
 * _strtok - Custom strtok implementation
 * @str: String to tokenize
 * @delim: Delimiters
 * Return: Pointer to next token or NULL
 */
char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *start;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);

	while (*next && is_delim(*next, delim))
		next++;

	if (*next == '\0')
	{
		next = NULL;
		return (NULL);
	}

	start = next;
	while (*next && !is_delim(*next, delim))
		next++;

	if (*next != '\0')
	{
		*next = '\0';
		next++;
	}
	else
		next = NULL;

	return (start);
}

/**
 * tokenize - Splits command line into array of words
 * @line: Input line
 * Return: Null-terminated array of strings
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token, *copy;
	int count = 0, i;

	if (line == NULL)
		return (NULL);
	copy = _strdup(line);
	if (copy == NULL)
		return (NULL);
	token = _strtok(copy, " \t\r\n\a");
	while (token != NULL)
	{
		count++;
		token = _strtok(NULL, " \t\r\n\a");
	}
	free(copy);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);
	copy = _strdup(line);
	if (copy == NULL)
	{
		free(tokens);
		return (NULL);
	}
	token = _strtok(copy, " \t\r\n\a");
	for (i = 0; i < count; i++)
	{
		tokens[i] = _strdup(token);
		token = _strtok(NULL, " \t\r\n\a");
	}
	tokens[count] = NULL;
	free(copy);
	return (tokens);
}
