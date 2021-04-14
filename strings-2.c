#include "shell.h"

/**
 * clean_comments - remove the comments from a buffer.
 * @buffer: buffer to clean.
 * Return: a pointer to the new (without comments) buffer.
 */
char *clean_comments(char *buffer)
{
	char *clean_buffer;
	int i = 0;

	clean_buffer = malloc(sizeof(char) * (str_len(buffer) + 1));
	if (!clean_buffer)
	{
		perror("MALLOC");
		return (NULL);
	}

	while (buffer[i])
	{
		if (buffer[i] == '#')
			break;
		clean_buffer[i] = buffer[i];
		i++;
	}
	clean_buffer[i] = '\0';

	return (clean_buffer);
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

/**
 * str_twins - compares two strings.
 * @s1: string 1.
 * @s2: string 2.
 * Return: 0 if s1 == s2, -1 if s1 != s2.
 */
int str_twins(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] != s2[i])
		return (-1);

	return (0);
}

/**
 * str_count - counts the number of times the char c is used in the buffer.
 * @buffer: buffer to check.
 * @c: char.
 * Return: number of repetitions +1.
 */
int str_count(char *buffer, char c)
{
	int i = 0;
	int counter = 0;

	while (buffer[i])
	{
		if (buffer[i] == c)
			counter++;
		i++;
	}

	return (counter + 1);
}

/**
 * str_tr - swap the character old_char by the character new_char
 * all the times it appears in the buffer.
 * @buffer: input buffer.
 * @old_char: char to be changed.
 * @new_char: char that replaces the old.
 * Return: the modified buffer.
 */
char *str_tr(char *buffer, char old_char, char new_char)
{
	int i = 0;
	char *new_buffer;

	new_buffer = str_dup(buffer);
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}

	i = 0;
	while (new_buffer[i])
	{
		if (new_buffer[i] == old_char)
			new_buffer[i] = new_char;
		i++;
	}

	return (new_buffer);
}
