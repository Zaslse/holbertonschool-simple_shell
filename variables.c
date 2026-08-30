#include "shell.h"

/**
 * get_env_value - Gets an environment variable value
 * @name: Variable name
 * @length: Variable name length
 *
 * Return: Variable value or empty string
 */
static char *get_env_value(char *name, int length)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, length) == 0 &&
		    environ[i][length] == '=')
			return (environ[i] + length + 1);
	}
	return ("");
}

/**
 * variable_length - Gets replacement length
 * @p: Variable position
 * @status: Last command status
 *
 * Return: Replacement length
 */
static int variable_length(char *p, int status)
{
	char number[32], *value;
	int length = 0;

	if (*p == '?')
	{
		sprintf(number, "%d", status);
		return (strlen(number));
	}
	if (*p == '$')
	{
		sprintf(number, "%d", getpid());
		return (strlen(number));
	}

	while ((p[length] >= 'a' && p[length] <= 'z') ||
	       (p[length] >= 'A' && p[length] <= 'Z') ||
	       (p[length] >= '0' && p[length] <= '9') ||
	       p[length] == '_')
		length++;

	value = get_env_value(p, length);
	return (strlen(value));
}

/**
 * expand_variables - Expands shell variables
 * @input: Command input
 * @status: Last command status
 *
 * Return: Expanded command
 */
char *expand_variables(char *input, int status)
{
	char *result, *value, number[32];
	int i, j = 0, length, size = 1;

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '$' && input[i + 1] != '\0')
		{
			size += variable_length(input + i + 1, status);
			i++;

			if (input[i] != '?' && input[i] != '$')
			{
				while ((input[i + 1] >= 'a' &&
					input[i + 1] <= 'z') ||
				       (input[i + 1] >= 'A' &&
					input[i + 1] <= 'Z') ||
				       (input[i + 1] >= '0' &&
					input[i + 1] <= '9') ||
				       input[i + 1] == '_')
					i++;
			}
		}
		else
			size++;
	}

	result = malloc(size);
	if (result == NULL)
		return (NULL);

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] != '$' || input[i + 1] == '\0')
		{
			result[j++] = input[i];
			continue;
		}

		i++;
		if (input[i] == '?')
			sprintf(number, "%d", status);
		else if (input[i] == '$')
			sprintf(number, "%d", getpid());
		else
		{
			length = 0;
			while ((input[i + length] >= 'a' &&
				input[i + length] <= 'z') ||
			       (input[i + length] >= 'A' &&
				input[i + length] <= 'Z') ||
			       (input[i + length] >= '0' &&
				input[i + length] <= '9') ||
			       input[i + length] == '_')
				length++;

			value = get_env_value(input + i, length);
			strcpy(result + j, value);
			j += strlen(value);
			i += length - 1;
			continue;
		}

		strcpy(result + j, number);
		j += strlen(number);
	}

	result[j] = '\0';
	return (result);
}
