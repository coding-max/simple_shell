#include "shell.h"

/**
 * str_len - returns the length of a string.
 * @s: string.
 * Return: Length of @s.
 */
int str_len(char *s)
{
	int i = 0;
	int cont = 0;

	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		cont++;
		i++;
	}
	return (cont);
}

/**
 * str_cpy - copy the string pointed to by src inluding the null byte
 * to the buffer pointed to by dest.
 * @dest: destination.
 * @src: source.
 * Return: @direction = pointer to dest.
 */
char *str_cpy(char *dest, char *src)
{
	char *direction = dest;

	while (*src)
		*dest++ = *src++;
	*dest = 0;
	return (direction);
}

/**
 * str_dup - returns a pointer to a new string which is a duplicate of str.
 * @str: source string to duplicate.
 * Return: pointer to the duplicated string.
 * or NULL if str = NULL or if insufficient memory was available.
 */
char *str_dup(char *str)
{
	char *aux;

	if (str == NULL)
		return (NULL);
	aux = malloc(sizeof(char) * (str_len(str) + 1));
	if (aux == NULL)
		return (NULL);
	return (str_cpy(aux, str));
}

/**
 * *str_cat - concatenates two strings.
 * @dest: destination.
 * @src: source.
 * Return: pointer to the resulting string dest.
 */
char *str_cat(char *dest, char *src)
{
	int i, j = 0;
	char *ptr = dest;

	if (src == NULL)
		return (ptr);
	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (; src[j] != '\0'; i++, j++)
		dest[i] = src[j];
	dest[i + 1] = src[j + 1];
	return (ptr);
}

/**
 * str_con - // TODO.
 * @s1: .
 * @s2: .
 * Return: .
 */
char *str_con(char *s1, char *s2)
{
	char *result = malloc(str_len(s1) + str_len(s2) + 1);
	/* TODO check for errors in malloc here */
	str_cpy(result, s1);
	strcat(result, s2);
	return (result);
}
