#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @tok: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *tok)
{
	int i, j, k, m, count = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!tok)
		tok = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!tok_delim(str[i], tok) && (tok_delim(str[i + 1], tok) || !str[i + 1]))
			count++;

	if (count == 0)
		return (NULL);
	s = malloc((1 + count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (tok_delim(str[i], tok))
			i++;
		k = 0;
		while (!tok_delim(str[i + k], tok) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
