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
