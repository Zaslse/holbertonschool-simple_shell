#include "shell.h"

/**
 * _strcat - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to destination
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0, j = 0;

	if (dest == NULL || src == NULL)
		return (dest);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strchr - Locates character in string
 * @s: String
 * @c: Character
 * Return: Pointer to char or NULL
 */
char *_strchr(const char *s, char c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/**
 * _atoi - Converts string to integer
 * @s: Input string
 * Return: Parsed integer or -1 on error
 */
int _atoi(const char *s)
{
	int i = 0;
	unsigned int num = 0;

	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	return ((int)num);
}

/**
 * _itoa - Converts integer to string
 * @n: Input integer
 * Return: Allocated string
 */
char *_itoa(int n)
{
	char buf[32];
	int i = 0, j, is_neg = 0;
	unsigned int num;
	char *res;

	if (n == 0)
		return (_strdup("0"));
	if (n < 0)
	{
		is_neg = 1;
		num = -n;
	}
	else
		num = n;
	while (num > 0)
	{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (is_neg)
		buf[i++] = '-';
	res = malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	for (j = 0; j < i; j++)
		res[j] = buf[i - 1 - j];
	res[i] = '\0';
	return (res);
}
