#include "shell.h"

/**
 * _strlen - returns the length of a string.
 * @s: string.
 * Return: Length of @s.
 */
int _strlen(char *s)
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
 * _strcpy - copy the string pointed to by src inluding the null byte
 * to the buffer pointed to by dest.
 * @dest: destination.
 * @src: source.
 * Return: @direction = pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	char *direction = dest;

	while (*src)
		*dest++ = *src++;
	*dest = 0;
	return (direction);
}

/* TODO */
/**
 * *_strcat - concatenates two strings.
 * @dest: destination.
 * @src: source.
 *
 * Return: pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
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
 * _strdup - returns a pointer to a new string which is a duplicate of str.
 * @str: source string to duplicate.
 * Return: pointer to the duplicated string.
 * or NULL if str = NULL or if insufficient memory was available.
 */
char *_strdup(char *str)
{
	char *aux;

	if (str == NULL)
		return (NULL);
	aux = malloc(sizeof(char) * (_strlen(str) + 1));
	if (aux == NULL)
		return (NULL);
	return (_strcpy(aux, str));
}

/**
 * concat - // TODO.
 * @s1: .
 * @s2: .
 * Return: .
 */
char *concat(char *s1, char *s2)
{
	char *result = malloc(_strlen(s1) + _strlen(s2) + 1);
	/* TODO check for errors in malloc here */
	_strcpy(result, s1);
	strcat(result, s2);
	return (result);
}
