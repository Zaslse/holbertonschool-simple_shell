#include "shell.h"

static char *alias_names[100];
static char *alias_values[100];
static int alias_count;

/**
 * find_alias - Finds an alias
 * @name: Alias name
 * @index: Pointer to alias index
 *
 * Return: Alias value or NULL
 */
char *find_alias(char *name, int *index)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(alias_names[i], name) == 0)
		{
			if (index != NULL)
				*index = i;
			return (alias_values[i]);
		}
	}
	return (NULL);
}

/**
 * set_alias - Creates or replaces an alias
 * @name: Alias name
 * @value: Alias value
 */
static void set_alias(char *name, char *value)
{
	int i;

	if (find_alias(name, &i) != NULL)
	{
		free(alias_values[i]);
		alias_values[i] = strdup(value);
		return;
	}

	if (alias_count < 100)
	{
		alias_names[alias_count] = strdup(name);
		alias_values[alias_count] = strdup(value);
		alias_count++;
	}
}

/**
 * next_alias - Parses the next alias argument
 * @p: Current input position
 * @value: Alias value
 *
 * Return: Alias name or NULL
 */
static char *next_alias(char **p, char **value)
{
	char *name, quote;

	while (**p == ' ' || **p == '\t')
		(*p)++;
	if (**p == '\0' || **p == '\n')
		return (NULL);

	name = *p;
	while (**p != '=' && **p != ' ' && **p != '\t' &&
		   **p != '\n' && **p != '\0')
		(*p)++;

	if (**p != '=')
	{
		if (**p != '\0')
			*(*p)++ = '\0';
		*value = NULL;
		return (name);
	}

	*(*p)++ = '\0';
	quote = 0;
	if (**p == '\'' || **p == '"')
		quote = *(*p)++;

	*value = *p;
	if (quote)
	{
		while (**p != quote && **p != '\0')
			(*p)++;
	}
	else
	{
		while (**p != ' ' && **p != '\t' &&
			   **p != '\n' && **p != '\0')
			(*p)++;
	}

	if (**p != '\0')
		*(*p)++ = '\0';

	return (name);
}

/**
 * handle_alias - Handles the alias builtin
 * @input: Alias command input
 *
 * Return: Always 0
 */
int handle_alias(char *input)
{
	char *p = input + 5, *name, *value;
	int i;

	while (*p == ' ' || *p == '\t')
		p++;

	if (*p == '\0' || *p == '\n')
	{
		for (i = 0; i < alias_count; i++)
			printf("%s='%s'\n", alias_names[i], alias_values[i]);
		return (0);
	}

	while ((name = next_alias(&p, &value)) != NULL)
	{
		if (value != NULL)
			set_alias(name, value);
		else
		{
			value = find_alias(name, NULL);
			if (value != NULL)
				printf("%s='%s'\n", name, value);
		}
	}
	return (0);
}

/**
 * free_aliases - Frees all aliases
 */
void free_aliases(void)
{
	int i;

	for (i = 0; i < alias_count; i++)
	{
		free(alias_names[i]);
		free(alias_values[i]);
	}
}
