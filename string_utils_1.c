#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: The string
 * Return: Length
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * _strcpy - Copies a string
 * @dest: Destination
 * @src: Source
 * Return: Destination pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: Difference
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strdup - Duplicates a string
 * @str: The string
 * Return: Duplicated string pointer
 */
char *_strdup(char *str)
{
	int len;
	char *dup;

	if (!str)
		return (NULL);
	len = _strlen(str);
	dup = malloc(len + 1);
	if (dup)
		_strcpy(dup, str);
	return (dup);
}
