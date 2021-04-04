#include "shell.h"

/**
 * _strtwins - compares two strings.
 * @s1: string 1.
 * @s2: string 2.
 * Return: 0 if s1 == s2, -1 if s1 != s2.
 */
int _strtwins(char *s1, char *s2)
{
	int i = 0;

	while ((s1[i] != '\0' && s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);

	return (1);
}

/* TODO idk */

/**
 * _strtoargv - pending.
 * 
 * 
 */
char **_strtoargv(char *input_buffer)
{
	int i = 0,  ac = 0;
	int argc = 1; // siempe hay al menos un argumento (nombre del programa)
	char **argv; // aca se van a cargar los argumentos
	char *current_string;
	char *str_to_put;

	while(input_buffer[i])
	{
		if (input_buffer[i] == ' ' && (input_buffer[i + 1] && (input_buffer[i + 1] != ' ' && input_buffer[i + 1] != '\n')))
			argc += 1;
		i++;
	}
	printf("str_arg runing...\n");
	printf("str_arg -> %i arg detected\n", argc);
	argv = malloc (sizeof(char*) * (argc + 1));
	if (argv == NULL)
	{
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}
	
	current_string = strtok(input_buffer, "\n");
	current_string = strtok(current_string, " "); // primer argumento
	while (ac < (argc + 1))
	{
		str_to_put = _strdup(current_string);
		argv[ac] = str_to_put;
		current_string = strtok(NULL, " ");
		//* test
		printf("str_arg -> argv[%i] = %s\n", ac, argv[ac]);
		ac++;
		
	}
	if (argc != (ac - 1))
		printf("ALERT: possible arguments counter error\n");

	printf("str_arg -> argc = %i | ac = %i\n", argc, ac);
	printf("str_arg closed...\n");

	return (argv);
}

/**
 * _strlen - returns the length of a string.
 * @s: string.
 *
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
 *
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
 *
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