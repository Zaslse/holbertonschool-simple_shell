#include "shell.h"

/**
 * variable_name_length - Gets variable name length
 * @name: Variable name
 *
 * Return: Variable name length
 */
static int variable_name_length(char *name)
{
	int length = 0;

	while ((name[length] >= 'a' && name[length] <= 'z') ||
	       (name[length] >= 'A' && name[length] <= 'Z') ||
	       (name[length] >= '0' && name[length] <= '9') ||
	       name[length] == '_')
		length++;

	return (length);
}

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
 * replacement_length - Gets variable replacement length
 * @p: Position after dollar sign
 * @status: Last command status
 *
 * Return: Replacement length
 */
static int replacement_length(char *p, int status)
{
	char number[32], *value;
	int length;

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

	length = variable_name_length(p);
	if (length == 0)
		return (1);

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
		if (input[i] != '$')
		{
			size++;
			continue;
		}

		if (input[i + 1] == '?' || input[i + 1] == '$')
		{
			size += replacement_length(input + i + 1, status);
			i++;
		}
		else
		{
			length = variable_name_length(input + i + 1);
			if (length == 0)
				size++;
			else
			{
				size += replacement_length(input + i + 1, status);
				i += length;
			}
		}
	}

	result = malloc(size);
	if (result == NULL)
		return (NULL);

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] != '$')
		{
			result[j++] = input[i];
			continue;
		}

		if (input[i + 1] == '?')
		{
			sprintf(number, "%d", status);
			strcpy(result + j, number);
			j += strlen(number);
			i++;
		}
		else if (input[i + 1] == '$')
		{
			sprintf(number, "%d", getpid());
			strcpy(result + j, number);
			j += strlen(number);
			i++;
		}
		else
		{
			length = variable_name_length(input + i + 1);
			if (length == 0)
			{
				result[j++] = '$';
				continue;
			}

			value = get_env_value(input + i + 1, length);
			strcpy(result + j, value);
			j += strlen(value);
			i += length;
		}
	}

	result[j] = '\0';
	return (result);
}
