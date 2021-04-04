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
 * not_empty - checks if buffer contains only spaces
 * @input_buffer: command line to be executed
 * Return: 0 if input_buffer contains only spaces, -1 if contains another char.
 */
int not_empty(char *input_buffer)
{
	int i = 0;
	int boolean = 0;

	while (input_buffer[i])
	{
		if (input_buffer[i] != ' ')
			break;
		i++;
	}
	if (input_buffer[i] && input_buffer[i] != '\n')
		boolean = -1;

	return (boolean);
}
