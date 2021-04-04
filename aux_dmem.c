#include "shell.h"

/**
 * create_argv - turns input_buffer into argument vector.
 * @input_buffer: input_buffer to be processed.
 * Return: a pointer to the new argument vector.
 */
char **create_argv(char *input_buffer)
{
	int i = 0,  ac = 0, argc = 1;
	char *current_string, *str_to_put;
	char **argv;

	while (input_buffer[i])
	{
		/**
		 * counter increases if current position is a space
		 * and following position not NULL, space nor \n
		 */
		if (input_buffer[i] == ' ' &&
			(input_buffer[i + 1] &&
				(input_buffer[i + 1] != ' ' &&
					input_buffer[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		/* TODO print error */
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

		current_string = strtok(input_buffer, "\n");
	current_string = strtok(current_string, " ");
	/* adds arguments to array */
	while (ac < (argc + 1))
	{
		/* duplicates argument and adds it to array */
		str_to_put = _strdup(current_string);
		argv[ac] = str_to_put;
		current_string = strtok(NULL, " ");
		ac++;

	}

	return (argv);
}

/**
 * free_argv - frees memory allocated in argument vector.
 * @argv: argument vector to be freed.
 */
void free_argv(char **argv)
{
	int i = 0;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
