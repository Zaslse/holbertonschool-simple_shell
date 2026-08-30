#include "shell.h"

/**
 * _strlen - Computes length of string
 * @s: Input string
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * _strcpy - Copies source string to destination
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == NULL || src == NULL)
		return (dest);
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
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(*s1 - *s2));
}

/**
 * _strncmp - Compares n bytes of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Max bytes
 * Return: 0 if equal, difference otherwise
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((int)(s1[i] - s2[i]));
	}
	return (0);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 * Return: Pointer to newly allocated string
 */
char *_strdup(const char *str)
{
	int len;
	char *dup;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_strcpy(dup, str);
	return (dup);
}
