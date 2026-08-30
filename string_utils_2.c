#include "shell.h"

/**
 * _strcat - Concatenates two strings
 * @dest: Destination
 * @src: Source
 * Return: Pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strchr - Locates a character in a string
 * @s: String
 * @c: Character
 * Return: Pointer to first occurrence or NULL
 */
char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

/**
 * _strncmp - Compares n bytes of two strings
 * @s1: First string
 * @s2: Second string
 * @n: Bytes to compare
 * Return: Difference
 */
int _strncmp(char *s1, char *s2, int n)
{
	while (n && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}

/**
 * _atoi - Converts string to integer
 * @s: The string
 * Return: The integer
 */
int _atoi(char *s)
{
	int res = 0, sign = 1, i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}
	for (; s[i] != '\0'; ++i)
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = res * 10 + s[i] - '0';
	}
	return (sign * res);
}
